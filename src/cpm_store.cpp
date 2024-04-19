/**
 * @file cpm_store.cpp
 * @brief Contains data storage code.
 * @version 0.1
 * @date 2024-02-10
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "cpm_store.h"

#include "misc.h"
#include <fstream>

/**
 * @brief Construct a new cpm store object.
 *
 * @param filepath
 */
cpm_store::cpm_store(const std::string &filepath)
{
  size = 0;
  load(filepath);
}

/**
 * @brief Load data from a file.
 *
 * @param filepath
 */
void cpm_store::load(const std::string &filepath)
{
  std::ifstream load_file(filepath);

  for (std::string line; std::getline(load_file, line);)
  {
    if (misc::has_contents(line, "\n"))
      line = line.substr(0, line.size() - 2);

    misc::trim(line);
    misc::remove_ch(line, ':');

    std::vector<std::string> _line(misc::split(line, " "));

    if (_line.size() >= 2)
      data[_line[0]] = _line[1];
    else if (1 == _line.size())
    {
    }
    else if ('[' == _line[1][0])
    {
      data[_line[0]] = std::vector<std::string>();

      misc::remove_ch(_line[1], '[');
      misc::remove_ch(_line[1], ']');
      misc::remove_ch(_line[1], ',');

      std::vector<std::string> value(misc::split(_line[1], " "));

      std::vector<std::string> &variant_vector(
          std::get<std::vector<std::string>>(data[_line[0]]));

      for (auto &_value : value)
        variant_vector.push_back(_value);
    }
  }

  load_file.close();
}

/**
 * @brief Returns reference to data stored.
 *
 * @return const storage_type&
 */
const storage_type &cpm_store::get() { return data; }

/**
 * @brief Check if key exists.
 *
 * @param key
 * @return true
 * @return false
 */
bool cpm_store::key_exists(const std::string &key) { return data.count(key); }
