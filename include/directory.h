/**
 * @file directory.h
 * @brief This file outlines directory.cpp.
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
    // ? Convert file into string
    std::string slurp(std::string dir, std::string filename);

    // ? Check if a string has specific contents
    bool has_contents(std::string text, std::string contents);

    bool has_file(std::string dir, std::string filename);

    bool has_folder(std::string dir, std::string foldername);

    void create_file(std::string dir, std::string filename);

    void create_folder(std::string dir, std::string foldername);

    void delete_file(std::string dir, std::string filename);
};