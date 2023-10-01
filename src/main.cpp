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
#include "logger.h"

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
        logger::error("no command provided");
        logger::flush_buffer();

        return 1;
    }

    std::string command = argv[1];
    logger::success("received " + command);

    // * Init command
    if (command == "init")
    {
        if (argc != 3)
        {   
            logger::error("invalid number of arguments for init command");
            logger::flush_buffer();

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
            
            logger::error("invalid number of arguments for pair command");
            logger::flush_buffer();

            return 3;
        }

        // * Assigning arguments
        std::string sub_command = argv[2];
        std::string file_name = argv[3];
        std::string language = (argc >= 5 && argv[4][0] != '-') ? argv[4] : NULL;
        std::vector<std::string> optionals = get_optionals(argc, argv);

        // * Sub commands
        if (sub_command == "new")
            commands::file_pair(commands::CREATE, file_name, language, optionals);
        else if (sub_command == "remove")
            commands::file_pair(commands::DELETE, file_name, language, optionals);
        else
        {
            logger::error("invalid sub-command for pair command");
            logger::flush_buffer();

            return 4;
        }
    }
    else if (command == "help")
    {
        commands::help();
    } else if (command == "--version" || command == "version")
    {
        commands::version();
    } else
    {
        logger::error("invalid command");
        logger::flush_buffer();

        return 5;
    }
    
    logger::success("finished command " + command);
    logger::flush_buffer();

    return 0;
}