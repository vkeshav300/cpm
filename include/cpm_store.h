/**
 * @file cpm_store.h
 * @brief Outlines cpm_store.cpp.
 * @version 0.1
 * @date 2024-02-10
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

#include <map>
#include <string>
#include <variant>
#include <vector>

typedef std::map<std::string,
                 std::variant<std::string, std::vector<std::string>>>
    storage_type;

class cpm_store {
private:
  storage_type data;
  size_t size;

public:
  cpm_store(const std::string &filepath);

  void load(const std::string &filepath);

  const storage_type &get();

  bool key_exists(const std::string &key);
};
