#pragma once

#include <string>

namespace commands
{
    // ? Creates directories and files needed for a basic C/C++ project.
    void init(std::string language);

    // ? Verifies "cpm init" has been run
    bool verify_init();

    // ? Downloads library from github link and puts files in proper folders.
    int install(std::string link);

    // ? Deletes library from library folders
    int uninstall(std::string name);
};