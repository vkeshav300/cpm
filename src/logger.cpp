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
        {"reset", "\x1b[0m"},
        {"black", "\x1b[1;38;5;0m"},
        {"red", "\x1b[1;38;5;9m"},
        {"green", "\x1b[1;38;5;10m"},
        {"yellow", "\x1b[1;38;5;11m"},
        {"blue", "\x1b[1;38;5;12m"},
        {"magenta", "\x1b[1;38;5;13m"},
        {"cyan", "\x1b[1;38;5;14m"},
        {"white", "\x1b[1;38;5;15m"},
        {"orange", "\x1b[1;38;5;202m"},
        {"purple", "\x1b[1;38;5;129m"},
        {"default", "\x1b[39m"}
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
        std::cout << colors["orange"]
                  << "[warning]: "
                  << colors["reset"]
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