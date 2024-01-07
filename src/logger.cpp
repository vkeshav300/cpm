/**
 * @file logger.cpp
 * @brief CPM's custom logger.
 * @version 0.1
 * @date 2023-11-11
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "logger.h"
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
        {"default", "\x1b[39m"},
    };

    int logger_count = 0;

    /**
     * @brief Flushes output buffer.
     *
     */
    void flush_buffer() { std::cout.flush(); }

    /**
     * @brief Handles logger count.
     *
     */
    void handle_logger_count()
    {
        std::cout << colors["cyan"]
                  << "["
                  << logger_count
                  << "]"
                  << colors["reset"];
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
     * @param mtype Message type.
     * @param color Message color.
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
     * @brief Logs y/n prompt to console.
     *
     * @param message
     * @return true
     * @return false
     */
    bool prompt(const std::string &message)
    {
        while (true)
        {
            handle_logger_count();

            std::string _prompt = colors["red"] + "[prompt]: " + colors["reset"] + message + "? [y/n]: ";
            std::cout << _prompt;

            std::string line;
            getline(std::cin, line);

            if ("y" == line || "yes" == line)
                return true;
            else if ("n" == line || "no" == line)
                return false;
            else
                warn("\"" + line + "\" is not a valid response, try again");
        }
    }
}