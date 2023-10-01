#include "logger.h"

#include <iostream>

namespace logger
{
    /**
     * @brief Logs success message to console.
     *
     * @param message
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
     * @param message
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
     * @param message
     */
    void custom(std::string message)
    {
    }

    /**
     * @brief Flushes output buffer.
     *
     */
    void flush_buffer()
    {
        std::cout << "" << std::endl;
    }
}