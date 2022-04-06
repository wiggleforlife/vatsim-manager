#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <algorithm>

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

int utils::askForChoice(const char* question, std::vector<std::string> choices) {
    char in[1];

    std::cout << question << std::endl;
    for (auto i = 0; i < choices.size(); ++i) {
        std::cout << "[" << i + 1 << "] : " << choices[i] << std::endl;
    }
    std::cout << std::endl << "Enter an option: ";
    std::cin.getline(in, 2, '\n');

    return std::stoi(in) - 1;
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

int utils::findInVector(std::vector<std::string> arr, std::string item) {
    for (auto i = 0; i < arr.size(); ++i) {
        if (iequals(arr[i], item))
            return i;
    }
    return -1;
}