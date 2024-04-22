/**
 * @file commands.h
 * @brief Outlines commands.cpp.
 * @version 0.1
 * @date 2023-09-29
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once

#include <string>
#include <vector>

namespace commands
{
    int init(const std::string language, const std::vector<std::string> &flags);

    int post_init(const std::string language);

    bool verify_init();

    int file_pair(const std::vector<std::string> &arguments, const bool hpp, const std::string language);

    int help();

    int version();

    int contents(const std::vector<std::string> &arguments, const std::vector<std::string> &flags);

    int install(const std::vector<std::string> &arguments, const std::vector<std::string> &flags, const std::string language);

    int uninstall(const std::vector<std::string> &arguments);
};
