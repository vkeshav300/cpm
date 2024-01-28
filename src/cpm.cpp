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
#include "directory.h"
#include "logger.h"
#include "misc.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
#include <curl/curl.h>

// * Finding OS
#ifdef _WIN32
#define OS_NAME "windows"
#elif __APPLE__
#define OS_NAME "macOS"
#elif __linux__
#define OS_NAME "linux"
#else
#define OS_NAME "null"
#endif

std::vector<std::string> all_commands = {
    "init",
    "pair",
    "help",
    "version",
    "contents",
    "insert",
    "install",
    "uninstall",
};

std::vector<std::string> init_exceptions = {
    "init",
    "help",
    "version",
    "contents",
};

std::vector<std::string> get_lang_from_first_arg = {
    "init",
};

/**
 * @brief Processes command.
 *
 * @param command
 * @param arguments
 * @param flags
 * @param language
 * @return int
 */
int process_command(std::string command, std::vector<std::string> arguments, std::vector<std::string> flags, std::string language)
{
    int r_code = 1;

    if ("init" == command)
    {
        if (misc::find_in_vector(flags, "post"))
        {
            r_code = commands::post_init(language);
            return r_code;
        }

        r_code = commands::init(language, flags);
    }
    else if ("pair" == command)
        r_code = commands::file_pair(arguments, (misc::find_in_vector(flags, "hpp")) ? true : false, language);
    else if ("help" == command)
        r_code = commands::help();
    else if ("version" == command)
        r_code = commands::version();
    else if ("contents" == command)
        r_code = commands::contents(arguments, flags);
    else if ("install" == command)
        r_code = commands::install(arguments, flags, language);
    else if ("uninstall" == command)
        r_code = commands::uninstall(arguments);

    return r_code;
}

/**
 * @brief Main function.
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char *argv[])
{
    auto start = std::chrono::high_resolution_clock::now();

    if (argc <= 1)
    {
        logger::error("no command provided");
        logger::flush_buffer();

        return 1;
    }

    std::string command = argv[1];
    std::vector<std::string> arguments;
    std::vector<std::string> flags;

    for (int i = 0; i < argc; i++)
    {
        std::string arg = argv[i];
        if ("-" == arg.substr(0, 1) && arg.size() >= 2)
            flags.push_back(arg.substr(1, arg.size()));
    }

    for (int i = 2; i < argc; i++)
    {
        std::string arg = argv[i];
        if (arg.substr(0, 1) != "-")
            arguments.push_back(arg);
    }

    logger::success("parsed command");

    if ("--version" == command)
        command = "version";

    if (!misc::find_in_vector(all_commands, command))
    {
        logger::error_q("is not a valid command", command);
        logger::flush_buffer();

        return 1;
    }

    bool initialized = commands::verify_init();
    bool command_is_exception = false;

    if (misc::find_in_vector(init_exceptions, command))
        command_is_exception = true;

    std::string language;

    if (initialized)
    {
        std::map<std::string, std::string> cpm_file = directory::parse_cpm("./", ".cpm");

        if (cpm_file.count("language") == false)
        {
            logger::error("directory contains invalid .cpm file");

            return 1;
        }

        language = cpm_file["language"];
    }
    else if (misc::find_in_vector(get_lang_from_first_arg, command))
        language = arguments[0];
    else if (misc::find_in_vector(init_exceptions, command))
        language = "c"; // ? Placeholder - doesn't actually matter
    else
    {
        logger::warn("directory must be initialized with cpm (use cpm help for more info)");
        logger::flush_buffer();

        return 1;
    }

    if ("c++" == language)
        language = "cpp";

    if ("c" != language && "cpp" != language)
    {
        logger::error("invalid language provided");
        return 1;
    }

    logger::custom("command \'" + command + "\' with " + std::to_string(arguments.size()) + " argument(s) and " + std::to_string(flags.size()) + " flag(s)", "received", "blue");

    curl_global_init(CURL_GLOBAL_DEFAULT);

    int result = process_command(command, arguments, flags, language);

    auto end = std::chrono::high_resolution_clock::now();

    logger::custom("command \'" + command + "\' with exit code " + std::to_string(result) + " in " + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) + " ms", "finished", "blue");
    logger::flush_buffer();

    curl_global_cleanup();

    return 0;
}