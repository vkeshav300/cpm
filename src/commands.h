#pragma once

namespace commands
{
    // ? Creates directories and files needed for a basic C/C++ project.
    void init(const char *language);

    // ? Process a inputted command and it's arguments
    void process(char *args[]);
};