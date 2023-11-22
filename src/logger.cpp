/**
 * @file logger.cpp
 * @brief CPM's custom logger
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
#include <string>

namespace logger
{
    /**
     * @brief Logs success message to console.
     *
     * @param message Text to be logged.
     */
    void success(std::string message)
    {
        std::cout << "\x1b[0;32m[success]: "
                  << colors["reset"]
                  << message
                  << "\n";
    }

    /**
     * @brief Logs error message to console.
     *
     * @param message Text to be logged.
     */
    void error(std::string message)
    {
        std::cerr << "\x1b[0;31m[error]: "
                  << colors["reset"]
                  << message
                  << "\n";
    }

    void error_q(std::string message, std::string quote)
    {
        error("\'" + quote + "\' " + message);
    }

    /**
     * @brief Logs custom message to console.
     *
     * @param message Text to be logged.
     * @param mtype The type of message (the text in between the square brackets).
     * @param color The color of the message.
     */
    void custom(std::string message, std::string mtype, std::string color)
    {
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