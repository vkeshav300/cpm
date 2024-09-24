/**
 * @file directory.cpp
 * @brief Contains most directory-related functions that aren't commands.
 * @version 0.1
 * @date 2023-09-29
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "directory.h"
#include "logger.h"
#include "misc.h"

#include <filesystem>
#include <fstream>

namespace directory
{
    /**
     * @brief Checks if directory exists at path.
     *
     * @param path
     * @return true
     * @return false
     */
    bool has_directory(const std::string &path)
    {
        return std::filesystem::is_directory(path);
    }

    /**
     * @brief Checks if file exists at a path.
     *
     * @param file
     * @return true
     * @return false
     */
    bool has_file(const std::string &path)
    {
        return std::filesystem::exists(path);
    }

    /**
     * @brief Creates directory at path.
     *
     * @param path
     */
    void create_directory(const std::string &path)
    {
        if (has_directory(path))
            return;

        std::filesystem::create_directory(path);
    }

    /**
     * @brief Create a file at path.
     * 
     * @param path 
     */
    void create_file(const std::string &path)
    {
        if (has_file(path))
            return;

        std::ofstream file(path);
        file.close();
    }

    /**
     * @brief Destroys file at path.
     * 
     * @param path 
     */
    void destroy_file(const std::string &path)
    {
        if (!has_file(path))
            return;

        std::filesystem::remove(path);
    }
} // namespace directory
