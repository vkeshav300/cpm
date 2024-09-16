/**
 * @file logger.h
 * @brief Outlines logger.cpp.
 * @version 0.1
 * @date 2023-09-30
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once

#include <map>
#include <string>
#include <vector>
#include <iostream>

class Logger
{
private:
    size_t logger_count = 0;

    Logger() {}

public:
    std::map<std::string, std::string> colors;

    Logger(const Logger &obj) = delete;

    static Logger &get();

    void set_colors(const std::map<std::string, std::string> &new_colors);

    void flush_buffer();

    void handle_logger_count();

    void success(const std::string &message);

    void success_q(const std::string &message, const std::string &quote);

    void error(const std::string &message);

    void error_q(const std::string &message, const std::string &quote);

    void warn(const std::string &message);

    void warn_q(const std::string &message, const std::string &quote);

    void custom(const std::string &message, const std::string &mtype, const std::string &color);

    std::string input(const std::string &message);

    std::string prompt(const std::string &message);

    bool prompt_yn(const std::string &message);
};