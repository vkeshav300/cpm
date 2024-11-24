/**
 * @file commands.h
 * @brief Outlines commands.cpp
 * @version 0.1
 * @date 2023-09-29
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once

#include "logger.h"

#include <string>
#include <vector>

namespace commands
{
    extern std::vector<std::string> supported_bases;

    int test(const std::vector<std::string> &args, const std::vector<std::string> &flags);

    int help(const std::vector<std::string> &args);

    int version();

    int create(const std::vector<std::string> &args, const std::vector<std::string> &flags);

    int file_pair(const std::vector<std::string> &args, const std::vector<std::string> &flags);

    int class_file_pair(const std::vector<std::string> &args, const std::vector<std::string> &flags);

    int config(const std::vector<std::string> &args, const std::vector<std::string> &flags);
};
