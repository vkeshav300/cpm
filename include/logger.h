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
        {"reset", "\x1b[0;0m"},
        {"black", "\x1b[0;30m"},
        {"red", "\x1b[0;31m"},
        {"green", "\x1b[0;32m"},
        {"yellow", "\x1b[0;33m"},
        {"blue", "\x1b[0;34m"},
        {"magenta", "\x1b[0;35m"},
        {"cyan", "\x1b[0;36m"},
        {"white", "\x1b[0;37m"},
        {"default", "\x1b[0;39m"},
    };

    // ? Success output
    void success(std::string message);

    // ? Error output
    void error(std::string message);

    // ? Error message "enquoting" certain string
    void error_q(std::string message, std::string quote);

    // ? Warning output
    void warn(std::string message);

    // ? Custom output
    void custom(std::string message, std::string mtype, std::string color);

    // ? Flushes buffer
    void flush_buffer();
}