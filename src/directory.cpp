#include "directory.h"

#include <fstream>
#include <iostream>
#include <direct.h>
#include <string.h>
#include <sys/stat.h>

bool directory::hasFile(std::string dir, std::string filename)
{
    // ? Checking to see if file exists
    struct stat metadata;

    if (stat((dir + filename).data(), &metadata) == 0 && !(metadata.st_mode & S_IFDIR))
        return true;

    return false;
}

bool directory::hasFolder(std::string dir, std::string foldername)
{
    // ? Checking to see if file exists
    struct stat metadata;

    if (stat((dir + foldername).data(), &metadata) == 0 && !(metadata.st_mode & S_IFDIR))
        return true;

    return false;
}

void directory::createFile(std::string dir, std::string filename)
{
    // ! Checking to see if the file already exists
    if (hasFile(dir, filename))
        return;

    // ? Creating file
    std::ofstream file(dir + filename);
    file.close();

    // ! Checking to see if folder creation worked
    if (hasFile(dir, filename) == false)
        std::cerr << "Error: " << strerror(errno) << "\n";
}

void directory::createFolder(std::string dir, std::string foldername)
{
    // ! Checking to see if the folder already exists
    if (hasFolder(dir, foldername))
        return;

    // ? Creating folder
    int success = mkdir((dir + foldername).data());

    // ! Checking to see if folder creation worked
    if (success == -1)
        std::cerr << "Error: " << strerror(errno) << "\n";
}