/**
 * @file commands.h
 * @brief Outlines commands.cpp
 * @version 0.1
 * @date 2023-09-29
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace commands {
extern std::vector<std::string> supported_bases;

uint8_t test(const std::vector<std::string> &args,
             const std::vector<std::string> &flags);

uint8_t help(const std::vector<std::string> &args);

uint8_t version();

uint8_t create(const std::vector<std::string> &args,
               const std::vector<std::string> &flags);

uint8_t file_pair(const std::vector<std::string> &args,
                  const std::vector<std::string> &flags);

uint8_t class_file_pair(const std::vector<std::string> &args,
                        const std::vector<std::string> &flags);

uint8_t struct_file_pair(const std::vector<std::string> &args,
                         const std::vector<std::string> &flags);

uint8_t config(const std::vector<std::string> &args,
               const std::vector<std::string> &flags);
}; // namespace commands
