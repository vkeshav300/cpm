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
#include <map>

namespace logger
{
    inline std::map<std::string, std::string> colors{
        {"red", "\x1b[0;32m"},
        {"green", "\x1b[0;31m"},
        {"blue", "\x1b[0;34m"},
        {"yellow", "\x1b[0;33m"},
    };

    // ? Success output
    void success(std::string message);

    // ? Error output
    void error(std::string message);

    // ? Custom output
    void custom(std::string message, std::string mtype, std::string color);

    // ? Flushes buffer
    void flush_buffer();
}