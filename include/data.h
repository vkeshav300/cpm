/**
 * @file data.h
 * @brief Defines Data_Manager singleton
 * @version 0.1
 * @date 2024-09-15
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

#include <string>
#include <unordered_map>

class Data_Manager {
private:
  Data_Manager() {}

public:
  std::unordered_map<std::string, std::string> config;

  Data_Manager(const Data_Manager& obj) = delete;

  static Data_Manager& get();

  void read();

  void write();

  bool config_has_key(const std::string& key);
};