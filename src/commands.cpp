#include "commands.h"
#include "directory.h"

void commands::init(const char *language)
{
    
}

void commands::process(char *argv[])
{
    const char *command = argv[1];

    if (command == "init")
        init(argv[2]);
}