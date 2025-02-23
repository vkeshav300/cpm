/**
 * @file misc.cpp
 * @brief Contains useful tools that don't warrant a dedicated category
 * @version 0.1
 * @date 2023-11-23
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "misc.h"
#include "logger.h"

#include <algorithm>
#include <cstdlib>
#include <filesystem>

namespace misc {
Logger &logger = Logger::get();

/**
 * @brief Checks if std::vector that contains std::strings has a specific string
 *
 * @param vector Vector to search
 * @param content Content to search for
 * @return true
 * @return false
 */
bool vector_contains(const std::vector<std::string> &vector,
                     const std::string &content) {
  return (std::find(vector.begin(), vector.end(), content) == vector.end())
             ? false
             : true;
}

/**
 * @brief Splits a std::string based on a specified delimeter
 *
 * @param s String to split
 * @param delimeter String to split by
 * @return std::vector<std::string>
 */
std::vector<std::string> split_string(const std::string &s,
                                      const std::string &delimiter) {

  std::vector<std::string> tokens;
  size_t start = 0, end = 0;

  if (delimiter.empty()) // Provided delimiter is ""
  {
    tokens.emplace_back(s);
    return tokens;
  }

  while ((end = s.find(delimiter, start)) != std::string::npos) {
    tokens.emplace_back(s.substr(start, end - start));
    start = end + delimiter.length();
  }

  tokens.emplace_back(s.substr(start));

  return tokens;
}

/**
 * @brief Gets the value of flags in the format of flag=value
 *
 * @param flag Raw flag
 * @return std::string
 */
std::string get_flag_value(const std::string &flag) {
  return (flag.find("=") != std::string::npos)
             ? flag.substr(flag.find("=") + 1, flag.length())
             : "";
}

/**
 * @brief Validates ofstream instance is open
 *
 * @param _ofstream Ofstream object
 * @return true
 * @return false
 */
bool ofstream_open(const std::ofstream &_ofstream) {
  if (!_ofstream.is_open()) {
    logger.custom("failed to open file", "ofs", "error");
    return false;
  }

  return true;
}

/**
 * @brief Validates ifstream instance is open
 *
 * @param _ifstream Ifstream object
 * @return true
 * @return false
 */
bool ifstream_open(const std::ifstream &_ifstream) {
  if (!_ifstream.is_open()) {
    logger.custom("failed to open file", "ifs", "error");
    return false;
  }

  return true;
}

/**
 * @brief Joins vector full of strings into one string
 *
 * @param vect Vector
 * @return std::string
 */
std::string join_string_vector(const std::vector<std::string> &vect,
                               const std::string &joiner) {
  std::string result;

  for (int i = 0; i < vect.size(); i++) {
    result += vect[i];

    if ((i + 1) < vect.size())
      result += joiner;
  }

  return result;
}

/**
 * @brief Capitalizes first letter after every separator (including first
 * letter)
 *
 * @param str String
 */
void auto_capitalize(std::string &str) {
  std::vector<std::string> split_str = split_string(str, "_");

  for (auto &token : split_str)
    token[0] = std::toupper(token[0]);

  str = misc::join_string_vector(split_str, "_");
}
} // namespace misc
