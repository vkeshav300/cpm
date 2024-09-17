/**
 * @file logger.cpp
 * @brief Provides majority of functionality to Logger singleton.
 * @version 0.1
 * @date 2023-11-11
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "logger.h"

#include <iostream>

/**
 * @brief Get method for logger class.
 *
 * @return Logger*
 */
Logger &Logger::get()
{
  static Logger logger;
  return logger;
}

/**
 * @brief Sets color map for logger.
 *
 * @param new_colors
 */
void Logger::set_colors(const std::map<std::string, std::string> &new_colors)
{
  colors = new_colors;
}

/**
 * @brief Flushes output buffer.
 *
 */
void Logger::flush_buffer() { std::cout.flush(); }

/**
 * @brief Handles logger count.
 *
 */
void Logger::handle_logger_count()
{
  std::cout << colors["cyan"] << "[" << logger_count << "]" << colors["reset"];
  if (logger_count < 10)
    std::cout << " ";

  if (logger_count < 100)
    std::cout << " ";

  logger_count++;
}

/**
 * @brief Logs success message to console.
 *
 * @param message Text to be logged.
 */
void Logger::success(const std::string &message)
{
  handle_logger_count();
  std::cout << colors["green"] << "[success]: " << colors["reset"] << message << "\n";
}

/**
 * @brief Logs success message with quote to console.
 *
 * @param message Text to be logged.
 * @param quote Text in quote.
 */
void Logger::success_q(const std::string &message, const std::string &quote)
{
  success("\'" + quote + "\' " + message);
}

/**
 * @brief Logs error message to console.
 *
 * @param message Text to be logged.
 */
void Logger::error(const std::string &message)
{
  handle_logger_count();
  std::cerr << colors["red"] << "[error]: " << colors["reset"] << message << "\n";
}

/**
 * @brief Logs error message with quote to console.
 *
 * @param message Text to be logged.
 * @param quote Text in quote.
 */
void Logger::error_q(const std::string &message, const std::string &quote)
{
  error("\'" + quote + "\' " + message);
}

/**
 * @brief Logs warning message to console.
 *
 * @param message
 */
void Logger::warn(const std::string &message)
{
  handle_logger_count();
  std::cout << colors["orange"] << "[warning]: " << colors["reset"] << message << "\n";
}

/**
 * @brief Logs warning message with quote to console.
 *
 * @param message Text to be logged.
 * @param quote Text in quote.
 */
void Logger::warn_q(const std::string &message, const std::string &quote)
{
  warn("\'" + quote + "\' " + message);
}

/**
 * @brief Logs custom message to console.
 *
 * @param message Text to be logged.
 * @param mtype Message type.
 * @param color Message color.
 */
void Logger::custom(const std::string &message, const std::string &mtype, const std::string &color)
{
  handle_logger_count();
  std::cout << colors[color] << "[" << mtype << "]: " << colors["reset"] << message << "\n";
}

/**
 * @brief Logs input to console.
 *
 * @param message Input prompt.
 * @return std::string
 */
std::string Logger::input(const std::string &message)
{
  handle_logger_count();

  std::string _input =
      colors["red"] + "[input]: " + colors["reset"] + message + ": ";
  std::cout << _input;

  std::string line;
  getline(std::cin, line);

  if (line.empty())
    line = "PLACEHOLDER";

  return line;
}

/**
 * @brief Logs an input prompt to console.
 *
 * @param message Prompt.
 * @return std::string
 */
std::string Logger::prompt(const std::string &message)
{
  handle_logger_count();

  std::cout << colors["magenta"] + "[prompt]: " + colors["reset"] + message + ": ";

  std::string line;
  getline(std::cin, line);

  return line;
}

/**
 * @brief Logs y/n prompt to console.
 *
 * @param message Prompt.
 * @return true
 * @return false
 */
bool Logger::prompt_yn(const std::string &message)
{
  while (true)
  {
    std::string line = prompt(message + " [y/n]");

    if (line == "y" || line == "yes")
      return true;
    else if (line == "n" || line == "no")
      return false;
    else
      warn_q("is not a valid response, try again", line);
  }
}