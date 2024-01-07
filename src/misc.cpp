/**
 * @file misc.cpp
 * @brief Contains useful tools that don't have a specific category.
 * @version 0.1
 * @date 2023-11-23
 *
 * @copyright Copyright (c) 2023
 *
 */
// ? Project headers
#include "misc.h"
#include "logger.h"

// ? Libraries
#include <algorithm>
#include <cctype>

namespace misc
{
    /**
     * @brief Creates sub-vector from a std::vector
     *
     * @param main_vector Initial vector.
     * @param begin_index Start index.
     * @param end_index End index.
     * @return std::vector<std::string>
     */
    std::vector<std::string> sub_vector(const std::vector<std::string> &main_vector, int begin_index, int end_index)
    {
        if (begin_index < 0 || end_index > static_cast<int>(main_vector.size()) || begin_index > end_index)
        {
            logger::error("invalid indicies for misc::sub_vector");
            return {};
        }

        return std::vector<std::string>(main_vector.begin() + begin_index, main_vector.begin() + end_index);
    }

    /**
     * @brief Checks if a string exists in a std::vector.
     *
     * @param main_vector Initial vector.
     * @param content Search for.
     * @return true
     * @return false
     */
    bool find_in_vector(const std::vector<std::string> &main_vector, std::string content)
    {
        return (std::find(main_vector.begin(), main_vector.end(), content) != main_vector.end());
    }

    /**
     * @brief Removes whitespaces at the beginning and end of strings.
     *
     * @param str Content.
     */
    void trim(std::string &str)
    {
        // * Trim leading whitespaces
        size_t start = str.find_first_not_of(' ');
        if (start != std::string::npos)
            str = str.substr(start);

        // * Trim trailing whitespaces
        size_t end = str.find_last_not_of(' ');
        if (end != std::string::npos)
            str = str.substr(0, end + 1);
    }

    /**
     * @brief Erases contents from std::vector.
     *
     * @param main_vector Initial vector.
     * @param contents Contents to remove.
     * @return int
     */
    void erase_from_vector(std::vector<std::string> &main_vector, const std::vector<std::string> &contents)
    {
        for (auto &_content : contents)
        {
            std::string content = _content;

            auto location = std::find(main_vector.begin(), main_vector.end(), content);

            // * Content does not exist in vector
            if (location == main_vector.end())
                continue;

            main_vector.erase(location);
        }
    }

    /**
     * @brief Check if flags contains a flag with specific content, then removes content from flag and returns it.
     * 
     * @param flags Command flags.
     * @param content 
     * @return std::string 
     */
    std::string get_flag_defined(const std::vector<std::string> &flags, const std::string &content)
    {
        for (auto &flag : flags)
            if (flag.find(content) != std::string::npos)
                return flag.substr(content.size(), flag.size() - 1);

        return "";
    }
}