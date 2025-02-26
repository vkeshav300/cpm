/**
 * @file logger.cpp
 * @brief Provides majority of functionality to Logger singleton
 * @version 0.1
 * @date 2023-11-11
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "logger.h"

#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>

/**
 * @brief Get method for logger class
 *
 * @return Logger*
 */
Logger &Logger::get() {
  static Logger logger;
  return logger;
}

/**
 * @brief Replaces old color maps with new color maps (only replaces given
 * color maps)
 *
 * @param new_colors New color map(s)
 */
void Logger::set_colors(
    const std::unordered_map<std::string, std::string> &new_colors) {
  for (const auto &[k, v] : new_colors)
    colors[k] = v;
}

/**
 * @brief Sets individual color map for logger ui
 *
 * @param k Color type
 * @param v Raw color
 */
void Logger::set_color(const std::string &k, const std::string &v) {
  colors[k] = v;
}

/**
 * @brief Disables text coloring for logger outputs
 *
 */
void Logger::disable_coloring() {
  for (auto &[k, v] : colors) {
    v = "";
  }
}

/**
 * @brief Flushes output buffer
 *
 */
void Logger::flush_buffer() const { std::cout.flush(); }

/**
 * @brief Handles logger count
 *
 */
void Logger::handle_logger_count() {
  static uint64_t logger_count = 0;

  std::cout << colors["count"] << "[" << logger_count++ << "]"
            << colors["reset"];

  if (logger_count < 10)
    std::cout << " ";

  if (logger_count < 100)
    std::cout << " ";
}

/**
 * @brief Logs success message to console
 *
 * @param message Text to be logged
 */
void Logger::success(const std::string &message) {
  handle_logger_count();
  std::cout << colors["success"] << "[success]: " << colors["reset"] << message
            << "\n";
}

/**
 * @brief Logs success message with quote to console
 *
 * @param message Text to be logged
 * @param quote Text in quote
 */
void Logger::success_q(const std::string &message, const std::string &quote) {
  success("\'" + quote + "\' " + message);
}

/**
 * @brief Logs error message to console
 *
 * @param message Text to be logged
 */
void Logger::error(const std::string &message) {
  handle_logger_count();
  std::cerr << colors["error"] << "[error]: " << colors["reset"] << message
            << "\n";
}

/**
 * @brief Logs error message with quote to console
 *
 * @param message Text to be logged
 * @param quote Text in quote
 */
void Logger::error_q(const std::string &message, const std::string &quote) {
  error("\'" + quote + "\' " + message);
}

/**
 * @brief Logs warning message to console
 *
 * @param message Text to be logged
 */
void Logger::warn(const std::string &message) {
  handle_logger_count();
  std::cout << colors["warn"] << "[warning]: " << colors["reset"] << message
            << "\n";
}

/**
 * @brief Logs warning message with quote to console
 *
 * @param message Text to be logged
 * @param quote Text in quote
 */
void Logger::warn_q(const std::string &message, const std::string &quote) {
  warn("\'" + quote + "\' " + message);
}

/**
 * @brief Logs custom message to console
 *
 * @param message Text to be logged
 * @param mtype Message type
 * @param color Message color
 */
void Logger::custom(const std::string &message, const std::string &mtype,
                    const std::string &color) {
  handle_logger_count();
  std::cout << ((raw_colors.find(color) != raw_colors.end()) ? raw_colors[color]
                                                             : colors[color])
            << "[" << mtype << "]: " << colors["reset"] << message << "\n";
}

/**
 * @brief Logs an input prompt to console
 *
 * @param message Prompt
 * @return std::string
 */
std::string Logger::prompt(const std::string &message) {
  handle_logger_count();

  std::cout << colors["prompt"] << "[prompt]: " << colors["reset"] << message
            << ": ";

  std::string line;
  getline(std::cin, line);

  return line;
}

/**
 * @brief Logs y/n prompt to console
 *
 * @param message Prompt
 * @return true
 * @return false
 */
bool Logger::prompt_yn(const std::string &message) {
  std::string response;
  while (true) {
    response = prompt(message + " [y/n]");

    if (response == "y" | response == "yes")
      return true;
    else if (response == "n" | response == "no")
      return false;
    else
      warn_q("is not a valid response, try again", response);
  }
}

/**
 * @brief Executes terminal command
 *
 * @param command Command to execute
 * @param must_populate_file Whether to throw error if command does not output
 * (optional)
 * @return true
 * @return false
 */
bool Logger::execute(const std::string &command,
                     const bool &must_populate_file) {
  handle_logger_count();

  /* Prefix */
  std::cout << colors["execute"] << "[executing]: " << colors["reset"]
            << command << "\n";

  /* Execution */
  std::system(command.c_str());

  /* Empty response is indicator of command execution failure */
  if (must_populate_file) {
    std::ifstream file("cpm.tmp");

    if (!file.is_open()) {
      error("could not open cpm.tmp");
      return false;
    }

    // Checks if cpm.tmp file is empty
    if (file.peek() == std::ifstream::traits_type::eof()) {
      error_q("did not execute successfully", command);
      file.close();

      return false;
    }

    file.close();
  }

  success_q("executed successfully", command);

  return true;
}