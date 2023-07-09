#include "directory.h"

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

void directory::slurp(std::ifstream &file, std::string *str)
{
    std::stringstream sstr;
    sstr << file.rdbuf();
    *str = sstr.str();
}

std::vector<std::string> splitString(const std::string &input, const std::string &delimiter)
{
    // * Split up string (tokens)
    std::vector<std::string> tokens;

    // * Positions (when iterating through string)
    std::size_t pos = 0;
    std::size_t nextPos;

    while ((nextPos = input.find(delimiter, pos)) != std::string::npos)
    {
        tokens.push_back(input.substr(pos, nextPos - pos));
        pos = nextPos + delimiter.length();
    }

    tokens.push_back(input.substr(pos));

    return tokens;
}

bool directory::hasContents(std::string text, std::string contents)
{
    if (text.find(contents) != std::string::npos)
        return true;

    return false;
}

bool directory::hasFile(std::string dir, std::string filename)
{
    std::string filepath = dir + filename;

    return std::filesystem::exists(filepath) && std::filesystem::is_regular_file(filepath);
}

bool directory::hasFolder(std::string dir, std::string foldername)
{
    std::string folderpath = dir + foldername;

    return std::filesystem::exists(folderpath) && std::filesystem::is_directory(folderpath);
}

void directory::createFile(std::string dir, std::string filename)
{
    std::string filepath = dir + filename;

    if (hasFile(dir, filename))
        return;

    std::ofstream file(filepath);
    file.close();

    if (!hasFile(dir, filename))
        std::cerr << "\x1b[0;31m"
                  << "Error: failed to create file\n"
                  << "\x1b[0m";
}

void directory::createFolder(std::string dir, std::string foldername)
{
    std::string folderpath = dir + foldername;

    if (hasFolder(dir, foldername))
        return;

    std::filesystem::create_directory(folderpath);

    if (!hasFolder(dir, foldername))
        std::cerr << "\x1b[0;31m"
                  << "Error: failed to create folder\n"
                  << "\x1b[0m";
}

void directory::deleteFile(std::string dir, std::string filename)
{
    std::string filepath = dir + filename;

    if (hasFile(dir, filename))
        return;

    std::filesystem::remove(filepath);

    if (hasFile(dir, filename))
        std::cerr << "\x1b[0;31m"
                  << "Error: failed to delete file\n"
                  << "\x1b[0m";
}