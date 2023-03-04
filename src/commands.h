#pragma once

#include <string>

namespace commands
{
    // ? Creates directories and files needed for a basic C/C++ project.
    void init(std::string language);

    // ? Process a inputted command and it's arguments
    void process(char *args[]);
};