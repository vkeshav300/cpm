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
#include <vector>

namespace logger
{
    extern std::map<std::string, std::string> colors;
    extern int logger_count;

    void flush_buffer();

    void handle_logger_count();

    void success(const std::string &message);

    void error(const std::string &message);

    void error_q(const std::string &message, const std::string &quote);

    void warn(const std::string &message);

    void custom(const std::string &message, const std::string &mtype, const std::string &color);

    bool prompt(const std::string &message);
}