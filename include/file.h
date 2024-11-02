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
#include <mutex>

class File
{
private:
  static std::ofstream writer;
  static std::ifstream reader;
  static std::mutex writer_mtx, reader_mtx;

  std::filesystem::path path;

  int wopen(const bool &append = true); // write open
  int ropen(); // read open

public:
  File();
  File(const std::filesystem::path &_path);

  void write(const std::vector<std::string> &lines);

  void load(const std::vector<std::string> &lines);

  void remove();
};