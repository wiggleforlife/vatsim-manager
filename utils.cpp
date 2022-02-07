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

bool utils::askForConfirmation(const char* program) {
    char in[1];

    std::cout << "Download install " << program << "? [Y/n]: ";
    std::cin.getline(in, 2, '\n');

    if (iequals(in, "y") || iequals(in, "")) {
        return true;
    } else {
        std::cout << "Operation cancelled by user" << std::endl << std::endl;
        return false;
    }

}