#pragma once

#include <string>

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

    // ? Create / Deletes file pairs (.h + [.cpp or .c])
    int file_pair(int method, std::string pair_name, std::string language);

    // ? Enums
    enum eFileMethods : std::size_t
    {
        CREATE = 0,
        DELETE
    };
};