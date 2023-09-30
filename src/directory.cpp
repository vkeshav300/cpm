/**
 * @file directory.cpp
 * @brief This file contains most directory-related functions that aren't commands.
 * @version 0.1
 * @date 2023-09-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "directory.h"

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

/**
 * @brief Reads file into string.
 * 
 * @param dir 
 * @param filename 
 * @return std::string 
 */
std::string directory::slurp(std::string dir, std::string filename)
{
    // * Checking if file exists
    if (!hasFile(dir, filename))
    {
        std::cerr << "\x1b[0;31m[error]: \x1b[0m\'"
                  << filename
                  << "\' does not exist at \'"
                  << dir
                  << "\'\n";
        
        return NULL;
    }

    // * Opening the file
    std::string filepath = dir + filename;

    std::ifstream file;
    file.open(filepath);

    // * Reading contents of the file
    std::string contents;
    char ch;
    
    while(file.get(ch))
        contents += ch;

    file.close();

    return contents;
}

/**
 * @brief Checks if a file has specific contents.
 * 
 * @param text 
 * @param contents 
 * @return true 
 * @return false 
 */
bool directory::hasContents(std::string text, std::string contents)
{
    if (text.find(contents) != std::string::npos)
        return true;

    return false;
}

/**
 * @brief Checks if directory has a file.
 * 
 * @param dir 
 * @param filename 
 * @return true 
 * @return false 
 */
bool directory::hasFile(std::string dir, std::string filename)
{
    std::string filepath = dir + filename;

    return std::filesystem::exists(filepath) && std::filesystem::is_regular_file(filepath);
}

/**
 * @brief Checks if directory has a folder.
 * 
 * @param dir 
 * @param foldername 
 * @return true 
 * @return false 
 */
bool directory::hasFolder(std::string dir, std::string foldername)
{
    std::string folderpath = dir + foldername;

    return std::filesystem::exists(folderpath) && std::filesystem::is_directory(folderpath);
}

/**
 * @brief Creates file in directory.
 * 
 * @param dir 
 * @param filename 
 */
void directory::createFile(std::string dir, std::string filename)
{
    std::string filepath = dir + filename;

    if (hasFile(dir, filename))
        return;

    std::ofstream file(filepath);
    file.close();

    if (!hasFile(dir, filename))
    {
        std::cerr << "\x1b[0;31m[error]: \x1b[0m"
                  << "failed to create file \'"
                  << filepath
                  << "\'\n";

        return;
    }

    std::cout << "\x1b[0;32m[success]: \x1b[0m"
              << "created file " 
              << filepath 
              << "\n";
}

/**
 * @brief Creates folder in directory.
 * 
 * @param dir 
 * @param foldername 
 */
void directory::createFolder(std::string dir, std::string foldername)
{
    std::string folderpath = dir + foldername;

    if (hasFolder(dir, foldername))
        return;

    std::filesystem::create_directory(folderpath);

    if (!hasFolder(dir, foldername))
    {
        std::cerr << "\x1b[0;31m[error]: \x1b[0m"
                  << "failed to create folder \'"
                  << folderpath
                  << "\'\n";

        return;
    }

    std::cout << "\x1b[0;32m[success]: \x1b[0m"
              << "created folder "
              << folderpath
              << "\n";
}

/**
 * @brief Deletes file in directory.
 * 
 * @param dir 
 * @param filename 
 */
void directory::deleteFile(std::string dir, std::string filename)
{
    std::string filepath = dir + filename;

    if (!hasFile(dir, filename))
        return;

    std::filesystem::remove(filepath);

    if (hasFile(dir, filename))
    {
        std::cerr << "\x1b[0;31m[error]: \x1b[0m"
                  << "failed to delete file \'"
                  << filepath
                  << "\'\n";

        return;
    }

    std::cout << "\x1b[0;32m[success]: \x1b[0m"
              << "deleted file "
              << filepath
              << "\n";
}