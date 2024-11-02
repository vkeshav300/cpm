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
#include <fstream>

namespace misc
{
    bool vector_contains(const std::vector<std::string> &vector, const std::string &content);

    std::vector<std::string> split_string(const std::string &s, const std::string &delimiter);

    std::string get_flag_value(const std::string &flag);

    bool ofstream_open(const std::ofstream &_ofstream);

    bool ifstream_open(const std::ifstream &_ifstream);

    /**
     * @brief Extracts sub-vector from vector
     * 
     * @tparam T 
     * @param parent_vector 
     * @param m1 min
     * @param m2 max
     * @return std::vector<T> 
     */
    template <typename T>
    std::vector<T> sub_vector(const std::vector<T> &parent_vector, const size_t &m1, const size_t &m2)
    {
        if (m1 > m2 || m2 > parent_vector.size())
            return {};

        std::vector<T> new_vector(parent_vector.begin() + m1, parent_vector.begin() + m2 + 1);
        return new_vector;
    }

    std::string join_string_vector(const std::vector<std::string> &vect, const std::string &joiner);
} // namespace misc
