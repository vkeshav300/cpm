#pragma once

#include <unordered_map>
#include <string>
#include <cstdint>

std::unordered_map<std::string, std::unordered_map<std::string, uint8_t>>
    command_info = {
        {
            "create",
            {
                {"min_args", 1},
            },
        },
        {
            "help",
            {
                {"min_args", 0},
            },
        },
        {
            "version",
            {
                {"min_args", 0},
            },
        },
        {
            "test",
            {
                {"min_args", 0},
            },
        },
        {
            "fpair",
            {
                {"min_args", 2},
            },
        },
        {
            "class",
            {
                {"min_args", 1},
            },
        },
        {
            "struct",
            {
                {"min_args", 1},
            },
        },
        {
            "config",
            {
                {"min_args", 2},
            },
        },
};