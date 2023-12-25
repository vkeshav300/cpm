/**
 * @file logger.cpp
 * @brief CPM's custom logger.
 * @version 0.1
 * @date 2023-11-11
 *
 * @copyright Copyright (c) 2023
 *
 */
// ? Project headers
#include "logger.h"

// ? Standard library
#include <iostream>

namespace logger
{
    std::map<std::string, std::string> colors = {
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

    int logger_count = 0;
    /**
     * @brief Handles logger count.
     * 
     */
    void handle_logger_count()
    {
        std::cout << colors["cyan"] << "[" << logger_count << "]";
        if (logger_count < 10)
            std::cout << " ";
        
        if (logger_count < 100)
            std::cout << " ";

        logger_count++;
    }

    /**
     * @brief Logs success message to console.
     *
     * @param message Text to be logged.
     */
    void success(const std::string &message)
    {
        handle_logger_count();
        std::cout << colors["green"]
                  << "[success]: "
                  << colors["reset"]
                  << message
                  << "\n";
    }

    /**
     * @brief Logs error message to console.
     *
     * @param message Text to be logged.
     */
    void error(const std::string &message)
    {
        handle_logger_count();
        std::cerr << colors["red"]
                  << "[error]: "
                  << colors["reset"]
                  << message
                  << "\n";
    }

    void error_q(const std::string &message, const std::string &quote)
    {
        error("\'" + quote + "\' " + message);
    }

    /**
     * @brief Logs warning message to console.
     * 
     * @param message 
     */
    void warn(const std::string &message)
    {
        handle_logger_count();
        std::cout << colors["yellow"]
                  << "[warning]: "
                  << message
                  << "\n";
    }

    /**
     * @brief Logs custom message to console.
     *
     * @param message Text to be logged.
     * @param mtype The type of message (the text in between the square brackets).
     * @param color The color of the message.
     */
    void custom(const std::string &message, const std::string &mtype, const std::string &color)
    {
        handle_logger_count();
        std::cout << colors[color]
                  << "["
                  << mtype
                  << "]: "
                  << colors["reset"]
                  << message
                  << "\n";
    }

    /**
     * @brief Flushes output buffer.
     *
     */
    void flush_buffer() { std::cout << std::endl; }
}