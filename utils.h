#include <iostream>

#ifndef VATSIM_MGR_UTILS_H
#define VATSIM_MGR_UTILS_H

#endif //VATSIM_MGR_UTILS_H

class utils {
public:
    bool iequals(const std::string& a, const std::string& b); //strcmp but case insensitive
    bool askForConfirmation(const char* program);
};