#include <iostream>
#include <cstring>
#include <curl/curl.h>
#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <sstream>
#include "utils.h"

using namespace std;

const char* version = "0.1.0";
vector<string> versions;
utils ut;

//TODO keep track of installed programs and add --refresh option

size_t write_data(char *ptr, size_t size, size_t nmemb, void *userdata) {
    std::ostringstream *stream = (std::ostringstream*)userdata;
    size_t count = size * nmemb;
    stream->write(ptr, count);
    return count;
}

//TODO move download function and make writing to output optional
string downloadVersions(int program) {

    cout << "Downloading program version numbers" << endl;

    CURL* curl = curl_easy_init();
    CURLcode res;
    const char* url = "https://raw.githubusercontent.com/wiggleforlife/vatsim-mgr/master/VERSIONS";
    ostringstream stream;

    if (!curl) {
        fprintf(stderr,"[-] Failed Initializing Curl\n");
        exit(-1);
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &stream);
    res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        fprintf(stderr,"[-] Could Not Fetch Webpage\n[+] Error: %s\n",curl_easy_strerror(res));
        cout << res << endl;
        exit(-2);
    }

    curl_easy_cleanup(curl);
    string line;
    string versionsTemp = stream.str();
    std::stringstream ss(versionsTemp);

    while(getline(ss, line, '\n')) {
        line = line.substr(line.find("=") + 1, line.length());
        versions.push_back(line);
    }

    return versions.at(program);
}

int downloadXpilot() {

    string programVersion = downloadVersions(0);

    cout << "Downloading xPilot " << programVersion << endl;

    CURL* curl = curl_easy_init();
    CURLcode res;
    //TODO move to temp dir
    FILE* output = fopen("xpilot.run", "wb");
    string url = "https://github.com/xpilot-project/xpilot/releases/download/v" + programVersion + "/xPilot-" +
            programVersion + "-linux-x64-installer.run";

    if (!curl) {
        fprintf(stderr,"[-] Failed Initializing Curl\n");
        exit(-1);
    }

    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEDATA,output);
    res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        fprintf(stderr,"[-] Could Not Fetch Webpage\n[+] Error: %s\n",curl_easy_strerror(res));
        cout << res << endl;
        exit(-2);
    }

    curl_easy_cleanup(curl);
    fclose(output);

    return 0;
}

//TODO confirm before installing
int install(char* program) {
    if (ut.iequals(program, "xpilot")) {
        downloadXpilot();
        system("chmod +x xpilot.run");
        system("./xpilot.run");
        system("rm xpilot.run");
    } else {
        cout << "Program name not recognised." << endl;
    }
    return 0;
}

int remove(char* program) {
    if (ut.iequals(program, "xpilot")) {
        system("rm -rf \"$HOME/.cache/Justin Shannon\"");
        system("$(find $HOME -name xPilot)/uninstall");
    } else {
        cout << "Program name not recognised." << endl;
    }
}

void showLicense() {
    cout << "This project is not endorsed by any VATSIM staff member." << endl;
    cout << "The xPilot 2.0.0 beta is licensed under GPL3. Redistribution is allowed under this license and express " <<
    "permission was given by Justin Shannon." << endl << endl;
    cout << "libcURL 7.81.0 has a custom license. Usage is allowed under this license." << endl << endl;
}

void showCommands() {
    cout << "-h - displays this page" << endl;
    cout << "-l - displays license information" << endl;
    cout << "-i - installs a pilot/ATC client from the following list - " << endl;
    cout << "     xPilot 2.0.0 beta (X-Plane 11)" << endl;
    cout << "-r - uninstalls a pilot/ATC client from the above list" << endl;
}

int main(int argc, char** argv) {

    cout << endl << "VATSIM Program Manager version " << version << " by Cian Ormond" << endl;
    cout << "Licensed under GPL3. For licensing of programs included, use -l." << endl << endl;

    //TODO remove this if statement bs
    //TODO add config option for xPilot's AppConfig
    if (argc > 1) {
        if (strcmp(argv[1], "-i") == 0) {
            if (argc > 2) {
                install(argv[2]);
            } else {
                cout << "Please specify a program to install. Available options are xpilot." << endl;
            }
        } else if (strcmp(argv[1], "-r") == 0) {
            if (argc > 2) {
                remove(argv[2]);
            } else {
                //TODO only show installed programs
                cout << "Please specify a program to uninstall. Available options are xpilot." << endl;
            }
        } else if (strcmp(argv[1], "-h") == 0) {showCommands();}
        else if (strcmp(argv[1], "-l") == 0) {showLicense();}
    } else {
        cout << "No command specified. Use the -h flag for a command list." << endl;
    }
    return 0;
}

