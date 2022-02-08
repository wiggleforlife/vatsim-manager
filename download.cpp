#include "download.h"
#include <vector>
#include <iostream>
#include <curl/curl.h>
#include <string>
#include <sstream>

size_t download::write_data(char *ptr, size_t size, size_t nmemb, void *userdata) {
    std::ostringstream *stream = (std::ostringstream*)userdata;
    size_t count = size * nmemb;
    stream->write(ptr, count);
    return count;
}

//TODO add progress indicator
std::vector<std::string> download::downloadPilotVersions() {

    std::cout << "Downloading program version numbers" << std::endl;

    CURL* curl = curl_easy_init();
    CURLcode res;
    const char* url = "https://raw.githubusercontent.com/wiggleforlife/vatsim-mgr/master/VERSIONS";
    std::ostringstream stream;

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
        std::cout << res << std::endl;
        exit(-2);
    }

    curl_easy_cleanup(curl);
    std::string line;
    std::string versionsTemp = stream.str();
    std::stringstream ss(versionsTemp);
    std::vector<std::string> versions;

    while(getline(ss, line, '\n')) {
        line = line.substr(line.find("=") + 1, line.length());
        versions.push_back(line);
    }

    return versions;
}

int download::downloadPilotClient(int program) {

    std::string programVersion = download::downloadPilotVersions().at(program);
    std::string programName;
    std::string url;

    switch(program) {
        case 0:
            programName = "xPilot";
            url = "https://github.com/xpilot-project/xpilot/releases/download/v" + programVersion + "/xPilot-" +
                programVersion + "-linux-x64-installer.run";
            break;
        case 1:
            programName = "Swift";
            url = "https://github.com/swift-project/pilotclient/releases/download/v" + programVersion + "/swiftinstal" +
                    "ler-linux-64-" + programVersion + ".run";
            break;
    }

    std::cout << "Downloading " << programName << " " << programVersion << std::endl;

    CURL* curl = curl_easy_init();
    CURLcode res;

    //TODO use installer in tmp if available, add --force-download flag
    std::system("mkdir -p /tmp/vatsim-manager");
    std::string outputName = "/tmp/vatsim-manager/" + programName + ".run";
    FILE* output = fopen(outputName.c_str(), "wb");

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
        std::cout << res << std::endl;
        exit(-2);
    }

    curl_easy_cleanup(curl);
    fclose(output);

    return 0;
}
