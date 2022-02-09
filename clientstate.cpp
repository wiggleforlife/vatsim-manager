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

int clientstate::createState() {

    if ((homedir = getenv("HOME")).c_str() == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }

    std::string write = gl_cs.version + '\n';
    std::vector<std::vector<std::string>> input = checkClients();
    /*
    for (int i = 0; i < input.size(); i++) {
        std::cout << input.at(i) << '\n';
    }
     */

    Json::Value stateOut;

    stateOut["installed"] = vectorToJson(input.at(0));
    stateOut["paths"] = vectorToJson(input.at(1));
    stateOut["versions"] = vectorToJson(input.at(2));

    std::ofstream out;
    out.open((homedir + "/.local/share/vatsim-manager/state.json").c_str());
    out << stateOut;
    out.close();

}

std::vector<std::vector<std::string>> clientstate::checkClients() {
    std::vector<std::vector<std::string>> res;
    std::vector<std::string> installed;
    std::vector<std::string> paths;
    std::vector<std::string> versions;

    //xpilot path from ~/.local/share/org.vatsim.xpilot/lastinstallpath.txt
    system("find ~/.local/share/org.vatsim.xpilot -name lastinstallpath.txt > /tmp/vatsim-manager/findres 2>&1");
    if (ut_cs.iequals(ut_cs.readFile("/tmp/vatsim-manager/findres"), homedir + "/.local/share/org.vatsim.xpilot/lastinstallpath.txt")) {

        installed.push_back("xpilot");

        paths.push_back(ut_cs.readFile((homedir + "/.local/share/org.vatsim.xpilot/lastinstallpath.txt").c_str()));

        //TODO xpilot version will be from a flag in the next update
        system((paths.at(0) + "/xPilot.AppImage --appimage-version > /tmp/vatsim-manager/findres 2>&1").c_str());
        versions.push_back(ut_cs.readFile("/tmp/vatsim-manager/findres"));
    }

    //swift path and version from ~/.local/share/org.swiftproject/apps.json
    system("find ~/.local/share/org.swiftproject/ -name apps.json > /tmp/vatsim-manager/findres 2>&1");
    if (ut_cs.iequals(ut_cs.readFile("/tmp/vatsim-manager/findres"), homedir + "/.local/share/org.swiftproject/apps.json")) {

        Json::Value swiftJson;
        std::ifstream swiftFile((homedir + "/.local/share/org.swiftproject/apps.json").c_str(), std::ifstream::binary);
        swiftFile >> swiftJson;

        installed.push_back("swift");
        //TODO remove /bin
        paths.push_back(swiftJson["containerbase"][0].get("exePath", "n").asString());
        versions.push_back(swiftJson["containerbase"][0].get("version", "n").asString());

    }


    res.push_back(installed);
    res.push_back(paths);
    res.push_back(versions);

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