/**
 * @file main.cpp
 * @brief This file puts together all the other files.
 * @version 0.1
 * @date 2023-09-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "commands.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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
    if (argc <= 1)
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
    else if (command == "help")
    {
        commands::help();
    }
    else
    {
        std::cerr << "\x1b[0;31m[error]: \x1b[0m"
                  << "invalid command"
                  << std::endl;

        return 5;
    }

    std::cout << "\x1b[0;32m[success]: \x1b[0m"
              << "finished command "
              << command
              << std::endl;

    return 0;
}