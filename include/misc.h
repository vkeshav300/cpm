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

#include <vector>
#include <string>

namespace misc
{
    // ? Extracts sub-vector from a vector
    std::vector<std::string> sub_vector(const std::vector<std::string> &main_vector, const int begin_index, const int end_index);

    // ? Checks if content is in a vector
    bool find_in_vector(const std::vector<std::string> &main_vector, std::string content);
}