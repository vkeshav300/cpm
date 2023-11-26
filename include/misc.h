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
    std::vector<std::string> sub_vector(const std::vector<std::string> &main_vector, int begin_index, int end_index);
}