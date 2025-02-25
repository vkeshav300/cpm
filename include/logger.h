/**
 * @file logger.h
 * @brief Defines Logger singleton
 * @version 0.1
 * @date 2023-09-30
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once

#include <string>
#include <unordered_map>
#include <vector>

class Logger {
private:
  Logger() {}

public:
  std::unordered_map<std::string, std::string> raw_colors = {
      {"reset", "\x1b[0m"},           {"black", "\x1b[1;38;5;0m"},
      {"red", "\x1b[1;38;5;9m"},      {"green", "\x1b[1;38;5;10m"},
      {"yellow", "\x1b[1;38;5;11m"},  {"blue", "\x1b[1;38;5;12m"},
      {"magenta", "\x1b[1;38;5;13m"}, {"cyan", "\x1b[1;38;5;14m"},
      {"white", "\x1b[1;38;5;15m"},   {"orange", "\x1b[1;38;5;202m"},
      {"purple", "\x1b[1;38;5;129m"}, {"default", "\x1b[39m"},
  };

  std::unordered_map<std::string, std::string> colors = {
      {"theme", raw_colors["blue"]},     {"success", raw_colors["green"]},
      {"error", raw_colors["red"]},      {"warn", raw_colors["orange"]},
      {"count", raw_colors["white"]},    {"prompt", raw_colors["cyan"]},
      {"execute", raw_colors["orange"]}, {"reset", raw_colors["reset"]},
  };

  Logger(const Logger &obj) = delete;

  static Logger &get();

  void set_colors(const std::unordered_map<std::string, std::string> &new_colors);

  void set_color(const std::string &k, const std::string &v);

  void disable_coloring();

  void flush_buffer() const;

  void handle_logger_count();

  void success(const std::string &message);

  void success_q(const std::string &message, const std::string &quote);

  void error(const std::string &message);

  void error_q(const std::string &message, const std::string &quote);

  void warn(const std::string &message);

  void warn_q(const std::string &message, const std::string &quote);

  void custom(const std::string &message, const std::string &mtype,
              const std::string &color);

  std::string prompt(const std::string &message);

  bool prompt_yn(const std::string &message);

  bool execute(const std::string &command,
               const bool &must_populate_file = true);
};