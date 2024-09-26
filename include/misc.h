/**
 * @file misc.h
 * @brief Outlines misc.cpp.
 * @version 0.1
 * @date 2023-11-23
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once

#include <string>
#include <vector>
#include <algorithm>

namespace misc
{
    bool vector_contains(const std::vector<std::string> &vector, const std::string &content);

    std::vector<std::string> split_string(const std::string &s, const std::string &delimiter);

    std::string get_flag_value(const std::string &flag);


} // namespace misc
