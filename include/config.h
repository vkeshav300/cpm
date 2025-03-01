/**
 * @file config.h
 * @brief Contains configuration variables for CPM (baked in at compile time via
 * constexpr char)
 * @version 0.1
 * @date 2025-02-26
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <cstdint>

/* Update managing */
constexpr char version_string[6] = "1.2.0";
constexpr char repo_link[60] =
    "https://api.github.com/repos/vkeshav300/cpm/releases/latest";
constexpr char updates_useragent[12] = "Mozilla/5.0";
constexpr uint16_t default_usc_freq = 5;

/* Init command */
constexpr char c_default_standard[3] = "23";
constexpr char cpp_default_standard[3] = "23";