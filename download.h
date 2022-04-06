#include <vector>
#include <string>

#ifndef VATSIM_MGR_DOWNLOAD_H
#define VATSIM_MGR_DOWNLOAD_H

#endif //VATSIM_MGR_DOWNLOAD_H


class download {
public:
    static std::vector<std::string> downloadPilotVersions();
    int downloadPilotClient(int program, int variant, bool force);
private:
    static size_t write_data(char *ptr, size_t size, size_t nmemb, void *userdata);
    static int progress_func(void* ptr, double TotalToDownload, double NowDownloaded, double TotalToUpload,
                                double NowUploaded);
};