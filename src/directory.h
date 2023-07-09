#pragma once

#include <string>
#include <fstream>
#include <vector>

namespace directory
{
    // ? Converts file into string
    void slurp(std::ifstream &file, std::string *str);

    // ? Splits string based off specific sequence of characters (delimiter)
    std::vector<std::string> splitString(const std::string &input, const std::string &delimiter);

    // ? Checks if a string has specific contents
    bool hasContents(std::string text, std::string contents);

    bool hasFile(std::string dir, std::string filename);

    bool hasFolder(std::string dir, std::string foldername);

    void createFile(std::string dir, std::string filename);

    void createFolder(std::string dir, std::string foldername);

    void deleteFile(std::string dir, std::string filename);
};