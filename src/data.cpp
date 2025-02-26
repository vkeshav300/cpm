/**
 * @file data.cpp
 * @brief Provides majority of functionality to Dat_Handler singleton
 * @version 0.1
 * @date 2024-09-15
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "data.h"
#include "directory.h"
#include "misc.h"

#include <cstdlib>
#include <fstream>

#ifdef _WIN32
/**
 * @brief Ensures existance of valid store location for cpm config data and
 * returns it (WINDOWS ONLY)
 *
 * @return std::string
 */
std::filesystem::path get_store_location() {
  return std::filesystem::absolute("");
}
#else
/**
 * @brief Ensures existance of valid store location for cpm config data and
 * returns it (NON-WINDOWS)
 *
 * @return std::string
 */
std::filesystem::path get_store_location() {
  /* /Users/<user>/.config/cpm */
  std::string home_loc = std::getenv("HOME");
  home_loc += "/.config";

  if (!directory::has_folder(home_loc))
    directory::create_folders({home_loc});

  home_loc += "/cpm";

  if (!directory::has_folder(home_loc))
    directory::create_folders({home_loc});

  return std::filesystem::absolute(home_loc);
}
#endif

/**
 * @brief Get method for Data_Manager singleton class
 *
 * @return Data_Manager&
 */
Data_Manager& Data_Manager::get() {
  static Data_Manager obj;
  return obj;
}

/**
 * @brief Reads config file and stores it in data
 *
 */
void Data_Manager::read() {
  std::string config_location = get_store_location();

  config_location += "/cpm.data";

  if (!directory::has_file(config_location))
    return;

  std::ifstream data_file(config_location);

  if (!misc::ifstream_open(data_file))
    return;

  /* Reading */
  char ch, prevCh;
  std::string key, value;
  bool onKey = true;

  /* Format --> key: value --> (key:<space>value\n) */
  while (data_file.get(ch)) {
    if (ch == '\n') // \n = newline = new key: value
    {
      config[key] = value;
      key = value = "";
      onKey = true;

      prevCh = ch;
      continue;
    } else if (prevCh == ':') // : = switch from key to value
    {
      prevCh = ch;
      continue;
    } else if (ch == ':') // space between colon and value
    {
      onKey = false;
      prevCh = ch;
      continue;
    }

    if (onKey) {
      key += ch;
      prevCh = ch;
      continue;
    }

    value += ch;
    prevCh = ch;
    continue;
  }

  config[key] = value;
}

/**
 * @brief Writes to config from stored information
 *
 */
void Data_Manager::write() {
  std::string config_location = get_store_location();

  std::ofstream data_file(config_location + "/cpm.data");

  if (!misc::ofstream_open(data_file))
    return;

  for (const auto& [k, v] : config) {
    if (k == "" | v == "")
      continue;

    data_file << k << ": " << v << "\n";
  }

  data_file.close();
}

/**
 * @brief Checks if config contains key
 *
 * @param key Key to check for
 * @return true
 * @return false
 */
bool Data_Manager::config_has_key(const std::string& key) {
  if (config.find(key) != config.end())
    return true;

  return false;
}