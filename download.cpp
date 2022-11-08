#include <vector>
#include <iostream>
#include <curl/curl.h>
#include <string>
#include <sstream>
#include <math.h>

#include "download.h"
#include "utils.h"

utils ut_dl;

size_t download::write_data(char *ptr, size_t size, size_t nmemb, void *userdata) {
    std::ostringstream *stream = (std::ostringstream*)userdata;
    size_t count = size * nmemb;
    stream->write(ptr, count);
    return count;
}

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

std::string download::downloadPilotClient(int program, int variant, bool force) {

    std::string programVersion = download::downloadPilotVersions().at(program);
    std::string programName;
    std::string url;

    switch(program) {
        case 0:
            programName = "xPilot";
            url = "https://github.com/xpilot-project/xpilot/releases/download/v" + programVersion + "/xPilot-" +
                  programVersion + "-linux-x64";
            switch (variant) {
                case 0:
                    url += "-ubuntu-latest-installer.run";
                    break;
                case 1:
                    url += "-ubuntu-18.04-installer.run";
                    break;
            }
            break;
        case 1:
            programName = "Swift";
            url = "https://github.com/swift-project/pilotclient/releases/download/v" + programVersion + "/swiftinstal" +
                    "ler-linux-64-" + programVersion + ".run";
            break;
    }

    std::cout << "Downloading " << programName << " " << programVersion << " variant " << variant + 1 << std::endl;

    CURL* curl = curl_easy_init();
    CURLcode res;

    std::string outputName = "/tmp/vatsim-manager/" + programName + programVersion + "-" + std::to_string(variant) + ".run";
    system(("find " + outputName + " > /tmp/vatsim-manager/findinstaller 2>&1")
                   .c_str());
    //TODO better solution for no reaction to if
    if (!ut_dl.iequals(ut_dl.readFile("/tmp/vatsim-manager/findinstaller"), outputName) || force) {}
    else {
        //TODO detect old versions
        std::cout << "Found installer in /tmp/vatsim-manager/" << std::endl << "If you encounter errors or this is an old " <<
             "installer, use --force-download" << std::endl << std::endl;
        return outputName;
    }

    FILE* output = fopen(outputName.c_str(), "wb");

    if (!curl) {
        fprintf(stderr,"[-] Failed Initializing Curl\n");
        exit(-1);
    }

    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, output);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);
    curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, progress_func);
    res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        fprintf(stderr,"[-] Could Not Fetch Webpage\n[+] Error: %s\n",curl_easy_strerror(res));
        std::cout << res << std::endl;
        exit(-2);
    }

    curl_easy_cleanup(curl);
    fclose(output);

    return outputName;
}

// https://stackoverflow.com/questions/1637587/c-libcurl-console-progress-bar
int download::progress_func(void* ptr, double TotalToDownload, double NowDownloaded, double TotalToUpload,
                            double NowUploaded)
{
    // ensure that the file to be downloaded is not empty
    // because that would cause a division by zero error later on
    if (TotalToDownload <= 0.0) {
        return 0;
    }

    // how wide you want the progress meter to be
    int totaldotz=40;
    double fractiondownloaded = NowDownloaded / TotalToDownload;
    // part of the progressmeter that's already "full"
    int dotz = (int) round(fractiondownloaded * totaldotz);

    // create the "meter"
    int ii=0;
    printf("%3.0f%% [",fractiondownloaded*100);
    // part  that's full already
    for ( ; ii < dotz;ii++) {
        printf("=");
    }
    // remaining part (spaces)
    for ( ; ii < totaldotz;ii++) {
        printf(" ");
    }
    // and back to line begin - do not forget the fflush to avoid output buffering problems!
    printf("]\r");
    fflush(stdout);
    // if you don't return 0, the transfer will be aborted - see the documentation
    return 0;
}
