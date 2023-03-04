#include "directory.h"

#include <fstream>
#include <iostream>
#include <direct.h>
#include <string.h>
#include <sys/stat.h>

bool directory::hasFile(const char *dir, const char *filename)
{
    // ? Full directory
    char buffer[sizeof(dir) + sizeof(filename) - 2];

    strncpy(buffer, dir, sizeof(buffer));
    strncpy(buffer, filename, sizeof(buffer));

    // ? Checking to see if file exists
    struct stat metadata;

    if (stat(buffer, &metadata) == 0 && !(metadata.st_mode & S_IFDIR))
        return true;

    return false;
}

bool directory::hasFolder(const char *dir, const char *foldername)
{
    // ? Full directory
    char buffer[sizeof(dir) + sizeof(foldername) - 2];

    strncpy(buffer, dir, sizeof(buffer));
    strncpy(buffer, foldername, sizeof(buffer));

    // ? Checking to see if file exists
    struct stat metadata;

    if (stat(buffer, &metadata) == 0 && !(metadata.st_mode & S_IFDIR))
        return true;

    return false;
}

void directory::createFile(const char *dir, const char *filename)
{
    // ! Checking to see if the file already exists
    if (hasFile(dir, filename))
        return;

    // ? Full directory
    char buffer[sizeof(dir) + sizeof(filename) - 2];

    strncpy(buffer, dir, sizeof(buffer));
    strncpy(buffer, filename, sizeof(buffer));

    std::ofstream file(filename);
    file.close();

    // ! Checking to see if folder creation worked
    if (hasFile(dir, filename) == false)
        std::cerr << "Error: " << strerror(errno) << "\n";
}

void directory::createFolder(const char *dir, const char *foldername)
{
    // ! Checking to see if the folder already exists
    if (hasFolder(dir, foldername))
        return;

    // ? Full directory
    char buffer[sizeof(dir) + sizeof(foldername) - 2];

    strncpy(buffer, dir, sizeof(buffer));
    strncpy(buffer, foldername, sizeof(buffer));

    // ? Creating folder
    int success = mkdir(buffer);

    // ! Checking to see if folder creation worked
    if (success == -1)
        std::cerr << "Error: " << strerror(errno) << "\n";
}