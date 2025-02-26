/**
 * @file directory.h
 * @brief Outlines directory.cpp
 * @version 0.1
 * @date 2023-09-29
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace directory {
bool has_folder(const std::filesystem::path &path);

bool has_file(const std::filesystem::path &path);

void create_folder(const std::filesystem::path &path);

void create_folders(const std::vector<std::filesystem::path> &paths);

void create_file(const std::filesystem::path &path);

void destroy_file(const std::filesystem::path &path);

std::string get_structure();

std::string get_extension();

std::filesystem::path get_structured_header_path(const std::string &name,
                                                 const bool &hpp = false);

std::filesystem::path get_structured_source_path(const std::string &name);
}; // namespace directory
