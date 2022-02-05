#include <iostream>

using namespace std;

char* version = "0.0.1";

//TODO return something for error checking
void install(char* program) {
    cout << "Installing " << program << endl;
}

int main(int argc, char** argv) {

    cout << "VATSIM Program Manager version " << version << " by Cian Ormond" << endl;
    cout << "This project is not endorsed by any VATSIM staff member." << endl;

    //TODO remove this if statement bs
    if (argc > 0) {
        if (argv[0] == "-i") {
            if (argc > 1) {
                install(argv[1]);
            } else {
                cout << "Please specify a program to install." << endl;
            }
        } else if (argv[0] == "-h") {
            //TODO write command list
            cout << "Command list is a WIP" << endl;
        }
    } else {
        cout << "No command specified. Use the -h flag for a command list." << endl;
    }
    return 0;
}

