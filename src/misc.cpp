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
 * @brief Checks if std::vector that contains std::strings has a specific
 * string
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

/**
 * @brief Returns a value based on how two paths are separated
 *
 * @param p1
 * @param p2
 */
char compare_paths(const std::filesystem::path &p1,
                   const std::filesystem::path &p2) {
  const std::vector<std::string> t_split(split_string(p1.string(), "/")),
      o_split(split_string(p2.string(),
                           "/")); // t_split = this_split, o_split = other_split
  size_t location = 0;

  for (; location <
         ((t_split.size() > o_split.size()) ? o_split.size() : t_split.size());
       location++) { // Iterate until smallest path size
    if (t_split[location] == o_split[location])
      continue;

    if (sub_vector(t_split, location, t_split.size() - 1).size() >
            sub_vector(o_split, location, o_split.size() - 1).size() |
        sub_vector(t_split, location, t_split.size() - 1).size() ==
            sub_vector(o_split, location, o_split.size() - 1).size())
      return -1; // p1 file is "further in" or "equally in" than p2 file
    else
      return 1; // p2 file is "further in" than p1 file
  }

  return 0; // fallback
}

/**
 * @brief Trims p1 relative to p2
 *
 * @param p1
 * @param p2
 * @return std::filesystem::path
 */
std::filesystem::path trim_path(const std::filesystem::path &p1,
                                const std::filesystem::path &p2) {
  const std::vector<std::string> t_split(split_string(p1.string(), "/")),
      o_split(split_string(p2.string(),
                           "/")); // t_split = this_split, o_split = other_split
  size_t location = 0;

  for (; location <
         ((t_split.size() > o_split.size()) ? o_split.size() : t_split.size());
       location++) // Iterate until smallest path size
    if (t_split[location] != o_split[location])
      break;

  return std::filesystem::path(misc::join_string_vector(
      misc::sub_vector(t_split, location, t_split.size() - 1), "/"));
}

/**
 * @brief Set the relative path needed to get from p1 to p2
 *
 * @param p Path to set
 * @param p1
 * @param p2
 */
void set_relative_path(std::string &p, const std::filesystem::path &p1,
                       const std::filesystem::path &p2) {
  /* Get relative path difference */
  const char path_diff(compare_paths(p1, p2));

  if (path_diff < 0) {
    /* Figure out last common path */
    const std::vector<std::string> split_header_p_path(
        split_string(std::filesystem::absolute(p2).string(), "/")),
        split_header_path(
            split_string(std::filesystem::absolute(p1).string(), "/"));
    size_t location = 0;

    for (; location < split_header_p_path.size(); location++)
      if (split_header_p_path[location] != split_header_path[location])
        break;

    /* Add ../ to path to get to last common path */
    for (size_t i = 0; i < (split_header_path.size() - location - 1); i++)
      p += "../";

    /* Add trimmed paths together */
    p += trim_path(p2, p1).parent_path().string();
  } else if (path_diff > 0)
    p += trim_path(p2, p1).parent_path().string() + "/";

  if (p[p.size() - 1] != '/')
    p += "/";

  if (p.length() > 0 && p[0] == '/')
    p = p.substr(1);
  else if (p.length() > 1 && (p[0] == '.' & p[1] == '/'))
    p = p.substr(2);
  p += p2.filename().string();
}

/**
 * @brief Replaces all instances if i1 with i2 in string s
 *
 * @param s
 * @param i1
 * @param i2
 */
void replace_string_instances(std::string &s, const std::string &i1,
                              const std::string &i2) {
  if (i1.empty() | i2.empty() | (i1 == i2))
    return;

  size_t pos = 0;

  while ((pos = s.find(i1, pos)) != std::string::npos) {
    s.replace(pos, i1.length(), i2);
    pos += i2.length();
  }
}
} // namespace misc
