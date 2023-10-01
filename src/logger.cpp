#include "logger.h"

#include <iostream>

namespace logger
{
    /**
     * @brief Logs success message to console.
     *
     * @param message Text to be logged.
     */
    void success(std::string message)
    {
        std::cout << "\x1b[0;32m[success]: \x1b[0m"
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
        std::cerr << "\x1b[0;31m[error]: \x1b[0m"
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
    void custom(std::string message, std::string mtype, std::string color)
    {
        std::cout << colors[color]
                  << "["
                  << mtype
                  << "]: \x1b[0m"
                  << message
                  << "\n";
    }

    /**
     * @brief Flushes output buffer.
     *
     */
    void flush_buffer()
    {
        std::cout << std::endl;
    }
}