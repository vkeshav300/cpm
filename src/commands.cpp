#include "commands.h"
#include "directory.h"

int commands::init(int language)
{
    unsigned int success = 0;

    switch (language)
    {
    case __CPM_LANG_C__:

        success = 0;
        break;

    case __CPM_LANG_CPP__:

        success = 0;
        break;

    default:
        success = 1;
        break;
    }

    return success;
}

int commands::process(const char *command, const char *arg)
{
    unsigned int success = 0;

    if (command == "init")
    {
        if (arg == "c")
        {
            success = init(__CPM_LANG_C__);
        }
        else if (arg == "cpp")
        {
            success = init(__CPM_LANG_CPP__);
        }
        else
        {
            success = 1;
        }
    }

    return success;
}