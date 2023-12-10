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
    // ? Create directories and files needed for a basic C/C++ project
    int init(const std::string language, const std::vector<std::string> &flags);

    // ? Adds .cpm file to project that has already been created
    int post_init(const std::string language);

    // ? Verify "cpm init" has been run
    bool verify_init();

    // ? Create / deletes file pairs ([.h + .hpp] + [.cpp or .c])
    int file_pair(const std::vector<std::string> &arguments, const bool hpp, const std::string language);

    // ? Lists commands + arguments + optional arguments
    int help();

    // ? Gives current version of CPM
    int version();

    // ? Manipulates contents of a file
    int contents(const std::vector<std::string> &arguments, const std::vector<std::string> &flags);

    // ? CURL --> Calculates total size of received data and appends it to a string
    size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *output);

    // ? Installs package from github repository in cpm format
    int install(const std::vector<std::string> &arguments, const std::vector<std::string> &flags, const std::string language);

    // ? Uninstalls package
    int uninstall(const std::vector<std::string> &arguments);
};