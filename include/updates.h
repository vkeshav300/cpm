/**
 * @file updates.h
 * @brief Handles scanning / updating CPM
 * @version 0.1
 * @date 2025-02-26
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <cstdint>

namespace updates {
uint8_t scan();

void auto_scan();
} // namespace updates