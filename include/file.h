/**
 * @file file.h
 * @brief Makes creating/loading/editing files easier
 * @version 0.1
 * @date 2024-11-01
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

#include <string>
#include <fstream>
#include <filesystem>
#include <vector>

class File
{
private:
  static std::ofstream writer;
  static std::ifstream reader;

  std::filesystem::path path;

public:
  File(const std::filesystem::path &_path);
  ~File();

  void write(const std::vector<std::string> &lines);

  void load(const std::vector<std::string> &lines);

  void remove();

  std::vector<std::string> read();

  void replace_first_with(const std::string &token_f, const std::string &token_r);

  bool exists(const std::string &token_f);

  std::filesystem::path get_path() const;

  char compare(const File &_f) const;

  std::filesystem::path trim(const File &_f) const;
};