#include "commands.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/*
! C/C++ Project Manager [CPM] General Information:
* - CPM stands for C/C++ Project Manager, not C/C++ Package Manager (although in the future it may support packages ;)
? - This project uses ANSI escape codes to color text. [https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797].
? - Please note that if a specific file (or chunk of code) is lacking comments, it usually is because the code is fairly straightforward and no comments are needed to those who can read the code.
*/
std::vector<std::string> get_optionals(int argc, char *argv[])
{
    std::vector<std::string> optionals;
    for (int i = 0; i < argc; i++)
    {
        std::string arg = argv[i];
        if (arg.substr(0, 1) == "-" && arg.size() >= 2)
            optionals.push_back(arg);
    }
    return optionals;
}

int main(int argc, char *argv[])
{
    if (argc < 1)
    {
        std::cerr << "\x1b[0;31m[error]: \x1b[0m"
                  << "no command provided"
                  << std::endl;

        return 1;
    }

    std::cout << "\x1b[0;32m[success]: \x1b[0m"
              << "received " << argv[1]
              << "\n";

    std::string command = argv[1];

    // * Init command
    if (command == "init")
    {
        if (argc != 3)
        {
            std::cerr << "\x1b[0;31m[error]: \x1b[0m"
                      << "invalid number of arguments for init command"
                      << std::endl;

            return 2;
        }

        commands::init(argv[2]);
    }

    // * Pair command
    else if (command == "pair")
    {
        if (argc < 4)
        {
            std::cerr << "\x1b[0;31m[error]: \x1b[0m"
                      << "invalid number of arguments for pair command"
                      << std::endl;

            return 3;
        }

        // * Assigning arguments
        std::string sub_command = argv[2];
        std::string file_name = argv[3];
        std::string language = (argc >= 5 && argv[4][0] != '-') ? argv[4] : "null";
        std::vector<std::string> optionals = get_optionals(argc, argv);

        // * Sub commands
        if (sub_command == "new")
            commands::file_pair(commands::CREATE, file_name, language, optionals);
        else if (sub_command == "remove")
            commands::file_pair(commands::DELETE, file_name, language, optionals);
        else
        {
            std::cerr << "\x1b[0;31m[error]: \x1b[0m"
                      << "invalid sub-command for pair command"
                      << std::endl;

            return 4;
        }
    }
    else
    {
        std::cerr << "\x1b[0;31m[error]: \x1b[0m"
                  << "invalid command"
                  << std::endl;

        return 5;
    }

    std::cout << "\x1b[0;32m[success]: \x1b[0m"
              << "finished command " << command << " successfully"
              << std::endl;

    return 0;
}