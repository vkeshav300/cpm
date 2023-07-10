#include "src/commands.h"

#include <iostream>
#include <fstream>
#include <string>

/*
! C/C++ Project Manager [CPM] General Information:
* - CPM stands for C/C++ Project Manager, not C/C++ Package Manager (although in the future it may support packages ;)
? - This project uses ANSI escape codes to color text. [https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797].
? - Please note that if a specific file (or chunk of code) is lacking comments, it usually is because the code is fairly straightforward and no comments are needed to those who can read the code.
*/

int main(int argc, char *argv[])
{
    if (argc < 1)
    {
        std::cerr << "\x1b[0;31m"
                  << "Error: No command provided"
                  << "\x1b[0m" << std::endl;
        return 1;
    }

    std::cout << "\x1b[0;32m"
              << "Command: " << argv[1]
              << "\x1b[0m\n";

    std::string command = argv[1];

    // * Init command
    if (command == "init")
    {
        if (argc != 3)
        {
            std::cerr << "\x1b[0;31m"
                      << "Error: Invalid number of arguments for init command"
                      << "\x1b[0m" << std::endl;
            return 2;
        }

        commands::init(argv[2]);
    }

    // * Test commaand
    else if (command == "test")
    {
        std::cout << "\x1b[0;33m"
                  << "Note: This command is to test the contents of the 'main' function of CPM."
                  << "\x1b[0m\n";
    }

    // * Pair command
    else if (command == "pair")
    {
        if (argc < 4 || argc > 5)
        {
            std::cerr << "\x1b[0;31m"
                      << "Error: Invalid number of arguments for pair command"
                      << "\x1b[0m" << std::endl;
            return 3;
        }

        std::string sub_command = argv[2];
        std::string file_name = argv[3];
        std::string language = (argc == 5) ? argv[4] : "CPM_FILE";

        if (sub_command == "add")
        {
            commands::file_pair(commands::CREATE, file_name, language);
        }
        else if (sub_command == "remove")
        {
            commands::file_pair(commands::DELETE, file_name, language);
        }
        else
        {
            std::cerr << "\x1b[0;31m"
                      << "Error: Invalid sub-command for pair command: " << sub_command
                      << "\x1b[0m" << std::endl;
            return 4;
        }
    }
    else
    {
        std::cerr << "\x1b[0;31m"
                  << "Error: Invalid command: " << command
                  << "\x1b[0m" << std::endl;
        return 5;
    }

    std::cout << "\x1b[0;32m"
              << "Finished command: " << command << "successfully"
              << "\x1b[0m" << std::endl;

    return 0;
}