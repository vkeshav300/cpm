#include "src/commands.h"

#include <iostream>
#include <fstream>
#include <string>

/*
! C/C++ Project Manager [CPM] General Information:
? - This project uses ANSI escape codes to color text. [https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797].
*/

int main(int argc, char *c_argv[])
{
    std::string argv[argc];

    for (int i = 0; i < argc; i++)
        argv[i] = (std::string) c_argv[i];

    std::cout << "\x1b[0;32m" << "Cast arguments\n" << "\x1b[0m";

    if (argv[1] == "init")
        commands::init(argv[2]);
    
    else
        std::cerr << "\x1b[0;31m" << "Error: No command for \'" << argv[1] << "\'" << "\x1b[0m" << std::endl;
        return 1;
    
    std::cout << "\x1b[0;32m" << "Finished" << "\x1b[0m" << std::endl;

    return 0;
}