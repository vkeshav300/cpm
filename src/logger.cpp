/**
 * @file logger.cpp
 * @brief Contains console logging code.
 * @version 0.1
 * @date 2023-11-11
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "logger.h"
#include <iostream>

namespace logger
{
  std::map<std::string, std::string> colors = {
      {"reset", "\x1b[0m"},
      {"black", "\x1b[1;38;5;0m"},
      {"red", "\x1b[1;38;5;9m"},
      {"green", "\x1b[1;38;5;10m"},
      {"yellow", "\x1b[1;38;5;11m"},
      {"blue", "\x1b[1;38;5;12m"},
      {"magenta", "\x1b[1;38;5;13m"},
      {"cyan", "\x1b[1;38;5;14m"},
      {"white", "\x1b[1;38;5;15m"},
      {"orange", "\x1b[1;38;5;202m"},
      {"purple", "\x1b[1;38;5;129m"},
      {"default", "\x1b[39m"},
  };

  size_t logger_count = 0;
  size_t debug_count = 0;

  /**
   * @brief Flushes output buffer.
   *
   */
  void flush_buffer() { std::cout.flush(); }

  /**
   * @brief Handles logger count.
   *
   */
  void handle_logger_count()
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
  void success(const std::string &message)
  {
    handle_logger_count();
    std::cout << colors["green"] << "[success]: " << colors["reset"] << message
              << "\n";
  }

  /**
   * @brief Logs success message with quote to console.
   *
   * @param message Text to be logged.
   * @param quote Text in quote.
   */
  void success_q(const std::string &message, const std::string &quote)
  {
    success("\'" + quote + "\' " + message);
  }

  /**
   * @brief Logs error message to console.
   *
   * @param message Text to be logged.
   */
  void error(const std::string &message)
  {
    handle_logger_count();
    std::cerr << colors["red"] << "[error]: " << colors["reset"] << message
              << "\n";
  }

  /**
   * @brief Logs error message with quote to console.
   *
   * @param message Text to be logged.
   * @param quote Text in quote.
   */
  void error_q(const std::string &message, const std::string &quote)
  {
    error("\'" + quote + "\' " + message);
  }

  /**
   * @brief Logs warning message to console.
   *
   * @param message
   */
  void warn(const std::string &message)
  {
    handle_logger_count();
    std::cout << colors["orange"] << "[warning]: " << colors["reset"] << message
              << "\n";
  }

  /**
   * @brief Logs warning message with quote to console.
   *
   * @param message Text to be logged.
   * @param quote Text in quote.
   */
  void warn_q(const std::string &message, const std::string &quote)
  {
    warn("\'" + quote + "\' " + message);
  }

  /**
   * @brief Logs debug message, acting as a "checkpoint" in the code.
   * 
   */
  void debug()
  {
    handle_logger_count();
    std::cout << colors["red"] << "[debug]: " << colors["reset"] << ++debug_count << "\n";
  }

  /**
   * @brief Logs custom message to console.
   *
   * @param message Text to be logged.
   * @param mtype Message type.
   * @param color Message color.
   */
  void custom(const std::string &message, const std::string &mtype,
              const std::string &color)
  {
    handle_logger_count();
    std::cout << colors[color] << "[" << mtype << "]: " << colors["reset"]
              << message << "\n";
  }

  /**
   * @brief Logs input to console.
   *
   * @param message Input prompt.
   * @return std::string
   */
  std::string input(const std::string &message)
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
   * @brief Logs y/n prompt to console.
   *
   * @param message Prompt.
   * @return true
   * @return false
   */
  bool yn_prompt(const std::string &message)
  {
    while (true)
    {
      handle_logger_count();

      std::string _prompt =
          colors["red"] + "[prompt]: " + colors["reset"] + message + "? [y/n]: ";
      std::cout << _prompt;

      std::string line;
      getline(std::cin, line);

      if ("y" == line || "yes" == line)
        return true;
      else if ("n" == line || "no" == line)
        return false;
      else
        warn_q("is not a valid response, try again", line);
    }
  }
} // namespace logger
