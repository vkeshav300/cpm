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

struct Update_Info {
    constexpr static char version[6] = "1.2.0";
    constexpr static char repo_link[60] = "https://api.github.com/repos/vkeshav300/cpm/releases/latest";
    constexpr static char useragent[12] = "Mozilla/5.0";
    constexpr static uint16_t default_usc_freq = 5; 
};

struct Standards {
    constexpr static char c[3] = "23";
    constexpr static char cpp[3] = "23";
};

extern Update_Info update_info;
extern Standards standards;