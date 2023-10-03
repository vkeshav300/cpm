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

    // ? Adds .cpm file to project that has already been created.
    int post_init(std::string language);

    // ? Verify "cpm init" has been run
    bool verify_init();

    // ? Create / deletes file pairs ([.h + .hpp] + [.cpp or .c])
    int file_pair(std::vector<std::string> *arguments, bool hpp, std::string language);

    // ? Lists commands + arguments + optional arguments
    int help();

    // ? Gives current version of CPM
    int version();
};