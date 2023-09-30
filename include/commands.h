/**
 * @file commands.h
 * @brief This file outlines commands.cpp.
 * @version 0.1
 * @date 2023-09-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <string>
#include <vector>

namespace commands
{
    // ? Create directories and files needed for a basic C/C++ project.
    int init(std::string language);

    // ? Verify "cpm init" has been run
    bool verify_init();

    // ? Download library from github link and puts files in proper folders.
    int install(std::string link, std::string tags);

    // ? Delete library from library folders
    int uninstall(std::string name);

    // ? Create / deletes file pairs ([.h + .hpp] + [.cpp or .c])
    int file_pair(int method, std::string pair_name, std::string language, std::vector<std::string> optionals);

    // ? Lists commands + arguments + optional arguments
    int help();

    // ? Enums
    enum eFileMethods : std::size_t
    {
        CREATE = 0,
        DELETE
    };
};