/**
 * @file directory.h
 * @brief Outlines directory.cpp.
 * @version 0.1
 * @date 2023-09-29
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once

#include <string>
#include <fstream>

namespace directory
{
    bool has_directory(const std::string &path);

    bool has_file(const std::string &path);

    void create_directory(const std::string &path);

    void create_file(const std::string &path);

    void destroy_file(const std::string &path);
}; // namespace directory
