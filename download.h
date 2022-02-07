#include <vector>
#include <string>

#ifndef VATSIM_MGR_DOWNLOAD_H
#define VATSIM_MGR_DOWNLOAD_H

#endif //VATSIM_MGR_DOWNLOAD_H


class download {
public:
    static std::vector<std::string> downloadPilotVersions();
    int downloadPilotClient(int program);
private:
    static size_t write_data(char *ptr, size_t size, size_t nmemb, void *userdata);
};