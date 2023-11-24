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
    // ? ANSI escape codes
    extern std::map<std::string, std::string> colors;

    // ? Message count
    extern int logger_count;

    // ? Injects logger count into stream + increments variable
    void handle_logger_count();

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