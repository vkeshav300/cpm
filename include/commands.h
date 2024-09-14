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

#include <iostream>
#include <string>
#include <vector>

namespace commands
{
    extern std::vector<std::string> base;
    
    bool verify_init();

    int help();

    int version();

    int create(const std::vector<std::string> &args);
};
