#include "directory.h"

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

bool directory::hasFile(std::string dir, std::string filename)
{
    std::string filepath = dir + filename;
    std::cout << std::filesystem::exists(filepath) << ":" std::filesystem::is_regular_file(filepath) << "\n";
    return std::filesystem::exists(filepath) && std::filesystem::is_regular_file(std::filesystem::status(filepath));
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

    std::fstream file(filepath);
    file.close();

    if (!hasFile(dir, filename))
        std::cerr << "\x1b[0;31m" << "Error: failed to create file" << "\n" << "\x1b[0m";
}

void directory::createFolder(std::string dir, std::string foldername)
{
    std::string folderpath = dir + foldername;

    if (hasFolder(dir, foldername))
        return;

    std::filesystem::create_directory(folderpath);

    if (!hasFolder(dir, foldername))
        std::cerr << "\x1b[0;31m" << "Error: failed to create folder" << "\n" << "\x1b[0m";
}