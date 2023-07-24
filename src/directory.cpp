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
        std::cerr << "\x1b[0;31m[error]: \x1b[0m"
                  << "failed to create file \'"
                  << filepath
                  << "\'\n";
}

void directory::createFolder(std::string dir, std::string foldername)
{
    std::string folderpath = dir + foldername;

    if (hasFolder(dir, foldername))
        return;

    std::filesystem::create_directory(folderpath);

    if (!hasFolder(dir, foldername))
        std::cerr << "\x1b[0;31m[error]: \x1b[0m"
                  << "failed to create folder \'"
                  << folderpath
                  << "\'\n";
}

void directory::deleteFile(std::string dir, std::string filename)
{
    std::string filepath = dir + filename;

    if (!hasFile(dir, filename))
        return;

    std::filesystem::remove(filepath);

    if (hasFile(dir, filename))
        std::cerr << "\x1b[0;31m[error]: \x1b[0m"
                  << "failed to delete file \'"
                  << filepath
                  << "\'\n";
}