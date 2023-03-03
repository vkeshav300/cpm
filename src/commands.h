#pragma once

// ? Different languages supported by CPM as enumerations
enum Langs
{
    __CPM_LANG_C__ = 0,
    __CPM_LANG_CPP__
};

namespace commands
{
    // ? Creates directories and files needed for a basic C/C++ project.
    int init(int language);

    // ? Process a inputted command and it's arguments
    int process(const char *command, const char *args);
};