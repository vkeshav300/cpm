/**
 * @file misc.cpp
 * @brief Contains useful tools that don't warrant a dedicated category.
 * @version 0.1
 * @date 2023-11-23
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "misc.h"
#include "logger.h"

#include <cstdlib>
#include <filesystem>

#ifdef _WIN32

std::string _get_store_location()
{
    return "";
}

#else

std::string _get_store_location()
{
    return "";
}

#endif

namespace misc
{
    Logger &logger = Logger::get();

    /**
     * @brief Checks if std::vector that contains std::strings has a specific string.
     *
     * @param vector Vector to search.
     * @param content Content to search for.
     * @return true
     * @return false
     */
    bool vector_contains(const std::vector<std::string> &vector, const std::string &content)
    {
        return (std::find(vector.begin(), vector.end(), content) == vector.end()) ? false : true;
    }

    /**
     * @brief Splits a std::string based on a specified delimeter.
     *
     * @param s String to split.
     * @param delimeter String to split by.
     * @return std::vector<std::string>
     */
    std::vector<std::string> split_string(const std::string &s, const std::string &delimiter)
    {
        std::vector<std::string> tokens;
        size_t start = 0;
        size_t end = 0;

        while ((end = s.find(delimiter, start)) != std::string::npos)
        {
            tokens.emplace_back(s.substr(start, end));
            start = end + delimiter.length();
        }

        tokens.emplace_back(s.substr(start));

        return tokens;
    }

    /**
     * @brief Get the flag value objectGets the value of flags in the format of -flag=value
     *
     * @param flag
     * @return std::string
     */
    std::string get_flag_value(const std::string &flag)
    {
        return (flag.find("=") != std::string::npos) ? flag.substr(flag.find("=") + 1, flag.length()) : "";
    }

    /**
     * @brief Validates ofstream instance is open.
     *
     * @param _ofstream
     * @return true
     * @return false
     */
    bool ofstream_open(const std::ofstream &_ofstream)
    {
        if (!_ofstream.is_open())
        {
            logger.custom("failed to open file", "ofs", "red");
            return false;
        }

        return true;
    }

    /**
     * @brief Validates ifstream instance is open.
     *
     * @param _ifstream
     * @return true
     * @return false
     */
    bool ifstream_open(const std::ifstream &_ifstream)
    {
        if (!_ifstream.is_open())
        {
            logger.custom("failed to open file", "ifs", "red");
            return false;
        }

        return true;
    }

    /**
     * @brief Returns location of cpm executable.
     *
     * @return char
     */
    std::string get_store_location()
    {
        std::string result = _get_store_location();

        return result;
    }
} // namespace misc
