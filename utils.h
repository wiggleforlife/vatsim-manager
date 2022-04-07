#include <iostream>
#include <vector>

#ifndef VATSIM_MGR_UTILS_H
#define VATSIM_MGR_UTILS_H

#endif //VATSIM_MGR_UTILS_H

class utils {
public:
    bool iequals(const std::string& a, const std::string& b); //strcmp but case insensitive
    bool askForConfirmation(const char* program);
    int askForChoice(const char* question, std::vector<std::string> choices);
    int findInVector(std::vector<std::string> v, std::string x);
    std::string readFile(const char* filename);
};