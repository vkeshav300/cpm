/**
 * @file file.cpp
 * @brief Gives functionality to file.h
 * @version 0.1
 * @date 2024-11-01
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "file.h"
#include "logger.h"
#include "misc.h"

/**
 * @brief Construct a new File:: File object
 *
 * @param _path
 */
File::File(const std::filesystem::path &_path)
    : path(std::filesystem::absolute(_path)) {
  std::filesystem::create_directories(
      std::filesystem::absolute(path.parent_path()));

  writer.open(path, std::ios::app);
  writer.close();
}

/**
 * @brief Destroy the File:: File object
 *
 */
File::~File() {
  writer.close();
  reader.close();
}

/**
 * @brief Writes (in append mode) lines to file
 *
 * @param lines Lines to write
 */
void File::write(const std::vector<std::string> &lines) {
  writer.open(path, std::ios::app);

  if (!misc::ofstream_open(writer))
    return;

  for (const auto &line : lines)
    writer << "\n" << line;

  writer.close();
}

/**
 * @brief Overwrites file with given lines
 *
 * @param lines Lines to write
 */
void File::load(const std::vector<std::string> &lines) {
  writer.open(path);

  if (!misc::ofstream_open(writer))
    return;

  for (const auto &line : lines)
    writer << line << "\n";

  writer.close();
}

/**
 * @brief Removes file from computer
 *
 */
void File::remove() {
  writer.close();
  reader.close();

  std::filesystem::remove(path);
}

/**
 * @brief Reads file into vector containing individual lines
 *
 * @return std::vector<std::string>
 */
std::vector<std::string> File::read() {
  reader.open(path);

  if (!misc::ifstream_open(reader))
    return {};

  std::vector<std::string> lines;
  std::string line;

  while (std::getline(reader, line))
    lines.emplace_back(line);

  return lines;
}

/**
 * @brief Finds first instance of 'token_f' in file and replaces it with
 * 'token_r'
 *
 * @param token_f Text to find
 * @param token_r Text to replace with
 */
void File::replace_first_with(const std::string &token_f,
                              const std::string &token_r) {
  const std::filesystem::path tmp_path(path.string() + ".tmp");

  writer.open(tmp_path);
  reader.open(path);

  if (!misc::ifstream_open(reader) | !misc::ofstream_open(writer))
    return;

  std::string line;
  size_t pos;
  bool searching = true;

  while (std::getline(reader, line)) {
    if (searching && (pos = line.find(token_f)) !=
                         std::string::npos) // Replcae first instance of token_f
                                            // with token_r
    {
      line.replace(pos, token_f.length(), token_r);
      searching = false; // Switch off searching mode
    }

    writer << line << "\n";
  }

  writer.close();
  reader.close();

  // Delete original file
  if (!std::filesystem::remove(path))
    return;

  /* Change temporary file into original file */
  std::filesystem::rename(tmp_path, path);
}

/**
 * @brief Returns whether 'token_f' exists in file
 *
 * @param token_f Text to find
 * @return true
 * @return false
 */
bool File::exists(const std::string &token_f) {
  reader.open(path);

  std::string current_token;
  char ch;

  while (reader.get(ch)) {
    if (ch == ' ' | ch == '\n') {
      current_token = "";
      continue;
    }

    std::string _ch(1, ch);
    current_token += _ch;

    if (current_token == token_f) {
      reader.close();
      return true;
    }
  }

  reader.close();
  return false;
}

/**
 * @brief Get the path member
 *
 * @return const std::filesystem::path
 */
std::filesystem::path File::get_path() const { return path; }

/**
 * @brief Gets relative location of another file (not lexiographically)
 *
 * @param _f Other file
 * @return char
 */
char File::compare(const File &_f) const {
  return misc::compare_paths(path, _f.get_path());
}

/**
 * @brief Returns the trimmed path of this file object by eliminating common
 * directories based on another file object
 *
 * @param _f Other file
 * @return std::filesystem::path
 */
std::filesystem::path File::trim(const File &_f) const {
  return misc::trim_path(path, _f.get_path());
}

std::ofstream File::writer;
std::ifstream File::reader;