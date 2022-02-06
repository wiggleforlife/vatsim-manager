#include "utils.h"
#include <iostream>

bool utils::iequals(const std::string& a, const std::string& b)
{
    return std::equal(a.begin(), a.end(),
                      b.begin(), b.end(),
                      [](char a, char b) {
                          return tolower(a) == tolower(b);
                      });
}

//TODO allow y/n to just be \n
bool utils::askForConfirmation(const char* program) {
    char* in;

    std::cout << "Download install " << program << "? [y/n]: ";
    std::cin >> in;

    if (iequals(in, "y")) {
        return true;
    } else {
        std::cout << "Operation cancelled by user" << std::endl;
        return false;
    }

}