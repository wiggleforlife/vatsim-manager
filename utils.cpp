#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>

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

    std::cout << "Download and install " << program << "? [Y/n]: ";
    std::cin.getline(in, 2, '\n');

    if (iequals(in, "y") || iequals(in, "")) {
        return true;
    } else {
        std::cout << "Operation cancelled by user" << std::endl << std::endl;
        return false;
    }

}

std::string utils::readFile(const char* filename) {
    std::filebuf fb;
    fb.open(filename, std::ios::in);

    std::istream is (&fb);
    std::ostringstream oss;
    oss << is.rdbuf();

    std::string output = oss.str();

    if (!output.empty() && output[output.length()-1] == '\n') {
        output.erase(output.length()-1);
    }

    return output;
}