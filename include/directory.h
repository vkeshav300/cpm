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

#include <fstream>
#include <filesystem>
#include <string>

namespace directory
{
    bool has_directory(const std::filesystem::path &path);

    bool has_file(const std::filesystem::path &path);

    void create_directory(const std::filesystem::path &path);

    void create_file(const std::filesystem::path &path);

    void destroy_file(const std::filesystem::path &path);

    std::string get_structure();

    std::string get_extension();
}; // namespace directory
