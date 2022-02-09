#include <vector>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <json/json.h>
#include <fstream>

#include "clientstate.h"
#include "utils.h"
#include "global.h"


utils ut_cs;
global gl_cs;

std::string homedir;

//TODO move to json config
int clientstate::createState() {

    if ((homedir = getenv("HOME")).c_str() == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }

    std::string write = gl_cs.version + '\n';
    std::vector<std::string> input = checkVersions();
    for (int i = 0; i < input.size(); i++) {
        std::cout << input.at(i) << '\n';
    }

}

std::vector<std::string> clientstate::checkVersions() {
    std::vector<std::string> res;


    //xpilot path from ~/.local/share/org.vatsim.xpilot/lastinstallpath.txt
    system("find ~/.local/share/org.vatsim.xpilot -name lastinstallpath.txt > /tmp/vatsim-manager/findres 2>&1");
    if (ut_cs.iequals(ut_cs.readFile("/tmp/vatsim-manager/findres"), homedir + "/.local/share/org.vatsim.xpilot/lastinstallpath.txt")) {

        res.push_back(ut_cs.readFile((homedir + "/.local/share/org.vatsim.xpilot/lastinstallpath.txt").c_str()));

        //TODO xpilot version will be from a flag in the next update
        system((res.at(0) + "/xPilot.AppImage --appimage-version > /tmp/vatsim-manager/findres 2>&1").c_str());
        res.push_back(ut_cs.readFile("/tmp/vatsim-manager/findres"));

    } else {
        res.push_back("n");
        res.push_back("n");
    }

    //swift path and version from ~/.local/share/org.swiftproject/apps.json
    system("find ~/.local/share/org.swiftproject/ -name apps.json > /tmp/vatsim-manager/findres 2>&1");
    if (ut_cs.iequals(ut_cs.readFile("/tmp/vatsim-manager/findres"), homedir + "/.local/share/org.swiftproject/apps.json")) {

        Json::Value swiftJson;
        std::ifstream swiftFile((homedir + "/.local/share/org.swiftproject/apps.json").c_str(), std::ifstream::binary);
        swiftFile >> swiftJson;

        //TODO remove /bin
        res.push_back(swiftJson["containerbase"].get("exePath", "n").asString());
        res.push_back(swiftJson["containerbase"].get("version", "n").asString());

    } else {
        res.push_back("n");
        res.push_back("n");
    }

    return res;
}

std::vector<std::string> clientstate::parseState() {
    std::vector<std::string> res;

    system("find /var/lib/vatsim-manager state > /tmp/vatsim-manager/findres 2>&1");
    if (ut_cs.iequals(ut_cs.readFile("/tmp/vatsim-manager/findres"), "/var/lib/vatsim-manager/state")) {

    } else {
        //TODO create state doc
        return parseState();
    }
    return res;
}


//store vatsim-manager version
//store client name and version