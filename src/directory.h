#pragma once

#include <string>
#include <fstream>

namespace directory
{
    // ? Converts file into string
    void slurp(std::ifstream &file, std::string *str);

    // ? Checks if a string has specific contents
    bool hasContents(std::string text, std::string contents);

    bool hasFile(std::string dir, std::string filename);

    bool hasFolder(std::string dir, std::string foldername);

    void createFile(std::string dir, std::string filename);

    void createFolder(std::string dir, std::string foldername);
};