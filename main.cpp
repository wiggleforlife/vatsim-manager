#include <iostream>
#include <cstring>

using namespace std;

char* version = "0.0.1";

//TODO return something for error checking
void install(char* program) {
    cout << "Installing " << program << endl;
}

int main(int argc, char** argv) {

    cout << "VATSIM Program Manager version " << version << " by Cian Ormond" << endl;
    cout << "This project is not endorsed by any VATSIM staff member." << endl << endl;

    //TODO remove this if statement bs
    if (argc > 1) {
        if (strcmp(argv[1], "-i") == 0) {
            if (argc > 2) {
                install(argv[2]);
            } else {
                cout << "Please specify a program to install." << endl;
            }
        } else if (strcmp(argv[1], "-h") == 0) {
            //TODO write command list
            cout << "Command list is a WIP" << endl;
        }
    } else {
        cout << "No command specified. Use the -h flag for a command list." << endl;
    }
    return 0;
}

