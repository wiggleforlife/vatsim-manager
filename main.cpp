#include <iostream>
#include <cstring>

using namespace std;

char* version = "0.0.1";

int downloadXpilot() {



    return 0;
}

//TODO return something for error checking
int install(char* program) {
    cout << "Installing " << program << endl;
    if (strcmp(program, "xpilot") == 0) {
        downloadXpilot();
    }
    return 0;
}

void showLicense() {
    cout << "This project is not endorsed by any VATSIM staff member." << endl;
    cout << "The xPilot 2.0.0 beta is licensed under GPL3. Redistribution is allowed under this license and express " <<
    "permission was given by Justin Shannon." << endl << endl;
    cout << "libCURL 7.81.0 has a custom license. Usage is allowed under this license." << endl << endl;
}

void showCommands() {
    cout << "-h - displays this page" << endl;
    cout << "-l - displays license information" << endl;
    cout << "-i - installs a pilot/ATC client from the following list - " << endl;
    cout << "     xPilot 2.0.0 beta (X-Plane 11)" << endl;
}

int main(int argc, char** argv) {

    cout << endl << "VATSIM Program Manager version " << version << " by Cian Ormond" << endl;
    cout << "Licensed under GPL3. For licensing of programs included, use -l." << endl << endl;

    //TODO remove this if statement bs
    if (argc > 1) {
        if (strcmp(argv[1], "-i") == 0) {
            if (argc > 2) {
                install(argv[2]);
            } else {
                cout << "Please specify a program to install. Available options are xpilot." << endl;
            }
        } else if (strcmp(argv[1], "-h") == 0) {showCommands();}
        else if (strcmp(argv[1], "-l") == 0) {showLicense();}
    } else {
        cout << "No command specified. Use the -h flag for a command list." << endl;
    }
    return 0;
}

