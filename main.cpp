#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "utils.h"
#include "download.h"
#include "global.h"
#include "clientstate.h"

using namespace std;

utils ut;
download dl;
global gl;
clientstate cs;

vector<vector<string>> state;

//TODO keep track of installed programs and add --refresh option

int install(const char* program, bool forceDownload) {

    string programName;
    int programIndex;
    int programVar = 0;

    if (ut.iequals(program, "xpilot")) {
        programName = "xPilot";
        programIndex = 0;
        programVar = ut.askForChoice("What build of xPilot would you like to download?",
                                     {"Ubuntu Latest", "Ubuntu 18.04"});
    } else if (ut.iequals(program, "swift")) {
        programName = "Swift";
        programIndex = 1;
    } else {
        cout << "Program name not recognised." << endl << endl;
        return 1;
    }

    string cmdOut;
    if (ut.askForConfirmation(programName.c_str())) {
        string outFile = dl.downloadPilotClient(programIndex, programVar, forceDownload);
        system(("chmod +x " + outFile).c_str());
        system((outFile).c_str());
        cs.createState();
    }


    return 0;
}

//TODO change to directory in state.json
int remove(const char* program) {
    if (ut.iequals(program, "xpilot")) {
        system("rm -rf \"$HOME/.cache/Justin Shannon\"");
        cout << "Launching uninstaller" << endl;
        system("$(find $HOME -name xPilot)/uninstall > /dev/null 2>&1");
    } else if (ut.iequals(program, "swift")) {
        //doesn't work if the qt sdk is installed
        system("$(find $HOME -name swift-*)/uninstall > /dev/null 2>&1");
    } else {
        cout << "Program name not recognised." << endl << endl;
        return 1;
    }
    cs.createState();
    return 0;
}

void showLicense() {
    cout << "This project is not endorsed by any VATSIM staff member." << endl;
    cout << "The xPilot 2.0.0 beta is licensed under GPL3. Express permission to redistribute the proprietary " <<
    "installer was given by Justin Shannon." << endl;
    cout << "The Swift beta is licensed under GPL3. Express permission to redistribute the proprietary installer was" <<
    "given by Mat Sutcliffe." << endl << endl;
    cout << "vSTARS is proprietary software. Express permission to redistribute the proprietary installer was given " <<
    "by Ross Carlson." << endl;
    cout << "vERAM is proprietary software. Express permission to redistribute the proprietary installer was given " <<
    "by Ross Carlson." << endl << endl;
    cout << "libcURL 7.81.0 has a custom license. Usage is allowed under this license." << endl << endl;
}

void showCommands() {
    cout << "-h - displays this page" << endl;
    cout << "-l - lists installed clients" << endl;
    cout << "-L - displays license information" << endl;
    cout << "-i - installs a pilot/ATC client from the following list - " << endl;
    cout << "     xPilot 2.0.0 beta (X-Plane 11), Swift (X-Plane 11, FlightGear)" << endl;
    cout << "-r - uninstalls a pilot/ATC client from the above list" << endl << endl;
}

void showClients() {
    std::string programName;
    for (int i = 0; i < state.at(0).size(); i++) {
        if (ut.iequals(state.at(0).at(i), "xpilot")) { programName = "xPilot"; }
        if (ut.iequals(state.at(0).at(i), "Swift")) { programName = "Swift"; }

        cout << programName << endl << "   " << state.at(1).at(i) << endl << "   " << state.at(2).at(i) << endl << endl;
    }
}

int main(int argc, char** argv) {

    cout << endl << "VATSIM Program Manager version " << gl.version << " by Cian Ormond" << endl;
    cout << "Licensed under GPL3. For licensing of programs included, use -L." << endl << endl;

    //TODO move this somewhere else
    cs.findHome();

    system("mkdir -p /tmp/vatsim-manager ~/.local/share/vatsim-manager");

    system("find ~/.local/share/vatsim-manager/ -name state.json > /tmp/vatsim-manager/findres 2>&1");
    if (ut.iequals(ut.readFile("/tmp/vatsim-manager/findres"), cs.homedir + "/.local/share/vatsim-manager/state.json")) {
        state = cs.parseState();
    } else { cs.createState(); }

    //TODO clean this up
    if (argc > 1) {

        if (strcmp(argv[1], "-i") == 0) {

            if (argc == 3) {
                install(argv[2], false);
            } else if (argc == 4) {
                if (ut.iequals(argv[3], "--force-download")) {
                    install(argv[2], true);
                } else if (ut.iequals(argv[2], "--force-download")) {
                    install(argv[3], true);
                } else {
                    install(argv[2], false);
                }
            }
            else {
                    //TODO only show uninstalled programs
                    cout << "Please specify a program to install. Available options are xPilot and Swift." << endl << endl;
            }

        } else if (strcmp(argv[1], "-r") == 0) {
            if (argc > 2) {
                remove(argv[2]);
            } else {
                //TODO only show installed programs
                cout << "Please specify a program to uninstall. Available options are xPilot and Swift." << endl
                     << endl;
            }
        }
        else if (strcmp(argv[1], "-h") == 0) {showCommands();}
        else if (strcmp(argv[1], "-L") == 0) {showLicense();}
        else if (strcmp(argv[1], "-l") == 0) {showClients();}
	else {
            cout << "Command not recognised. Use the -h flag for a command list" << endl << endl;
        }

    } else {
        cout << "No command specified. Use the -h flag for a command list." << endl << endl;
    }
    return 0;
}

