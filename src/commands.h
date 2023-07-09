#pragma once

#include <string>

namespace commands
{
    // ? Creates directories and files needed for a basic C/C++ project.
    int init(std::string language);

    // ? Verifies "cpm init" has been run
    bool verify_init();

    // ? Downloads library from github link and puts files in proper folders.
    int install(std::string link, std::string tags);

    // ? Deletes library from library folders
    int uninstall(std::string name);

    // ? Creates / Deletes file pairs ([.hpp or .h] + [.cpp or .c])
    int file_pair(int method, std::string language);
};