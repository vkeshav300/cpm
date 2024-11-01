/**
 * @file file.h
 * @brief Makes creating/loading/editing files easier.
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

  int wopen(); // read open
  int ropen(); // write open

public:
  File(const std::filesystem::path &_path);

  void write_line(const std::string &line);

  void write_lines(const std::vector<std::string> &lines);
};