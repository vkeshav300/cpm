/**
 * @file logger.h
 * @brief This file outlines logger.cpp.
 * @version 0.1
 * @date 2023-09-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <string>

namespace logger
{
    // ? Success output
    void success(std::string message);

    // ? Error output
    void error(std::string message);

    // ? Custom output
    void custom(std::string message);

    // ? Flushes buffer
    void endl();
}