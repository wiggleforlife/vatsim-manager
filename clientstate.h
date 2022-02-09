#include <iostream>
#include <vector>

#ifndef VATSIM_MANAGER_CLIENTSTATE_H
#define VATSIM_MANAGER_CLIENTSTATE_H


class clientstate {
public:
    int createState();
    std::vector<std::string> parseState();
private:
    std::vector<std::string> checkVersions();
};


#endif //VATSIM_MANAGER_CLIENTSTATE_H
