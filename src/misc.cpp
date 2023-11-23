/**
 * @file misc.cpp
 * @brief Contains useful tools that don't have a specific category.
 * @version 0.1
 * @date 2023-11-23
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "misc.h"
#include "logger.h"

namespace misc
{
    /**
     * @brief Creates sub-vector from a std::vector
     *
     * @param main_vector
     * @param begin_index
     * @param end_index
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
}