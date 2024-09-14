/**
 * @file misc.cpp
 * @brief Contains useful tools that don't warrant a dedicated category.
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
     * @brief Checks if std::vector that contains std::strings has a specific string.
     * 
     * @param vector Vector to search.
     * @param content Content to search for.
     * @return true 
     * @return false 
     */
    bool vector_contains(const std::vector<std::string> &vector, const std::string &content)
    {
        return (std::find(vector.begin(), vector.end(), content) == vector.end()) ? false : true;
    }
} // namespace misc
