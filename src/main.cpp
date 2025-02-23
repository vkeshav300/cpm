/**
 * @file main.cpp
 * @brief Main file
 * @version 0.1
 * @date 2023-09-29
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "commands.h"
#include "data.h"
#include "directory.h"
#include "logger.h"

#define MAIN_CONFIG_INCLUDE
#include "config.h"
#undef MAIN_CONFIG_INCLUDE

#include <chrono>
#include <cstdint>
#include <string>
#include <vector>

/**
 * @brief Main function
 *
 * @param argc Number of arguments
 * @param argv Arguments
 * @return int
 */
int main(int argc, char *argv[]) {
  /* Start time */
  const auto start = std::chrono::high_resolution_clock::now();

  /* Singletons */
  Logger &logger = Logger::get();
  Data_Handler &data_handler = Data_Handler::get();

  data_handler.read();

  /* Overwrites colormap with config variables */
  for (const auto &[k, v] : logger.colors) {
    if (data_handler.config_has_key("color_" + k))
      logger.set_color(k, logger.raw_colors[data_handler.config["color_" + k]]);
  }

  /* Checks if command was inputted */
  if (argc <= 1) {
    logger.error("no command provided");
    logger.flush_buffer();

    return 1;
  }

  /* Parsing information necessary for checks */
  const std::string command = argv[1];
  bool command_found = false;

  /* Checks if command exists */
  for (const auto &[k, v] : command_info) {
    if (k == command) {
      command_found = true;
      break;
    }
  }

  if (!command_found) {
    logger.error_q("is not a valid command", command);
    return 1;
  }

  /* Main parsing */
  std::vector<std::string> arguments;
  std::vector<std::string> flags;

  /* Flags */
  for (int i = 0; i < argc; i++) {
    std::string arg = argv[i];
    if (arg[0] == '-' & arg.size() > 1) {
      uint32_t _start = 1;
      if (arg[1] == '-' & arg.size() > 2) // --flag
        _start = 2;

      flags.push_back(arg.substr(_start, arg.size())); // -f
    }
  }

  /* Arguments */
  for (int i = 2; i < argc; i++) {
    std::string arg = argv[i];
    if (arg[0] != '-')
      arguments.push_back(arg);
  }

  logger.success("parsed command");

  /* Checks if minimum arguments requirement is met */
  if (arguments.size() < command_info[command]["min_args"]) {
    logger.error_q("requires at least " +
                       std::to_string(command_info[command]["min_args"]) +
                       " arguments",
                   command);
    return 1;
  }

  /* Command execution */
  uint8_t result = 0;

  if (command == "help")
    result = commands::help(arguments);
  else if (command == "version")
    result = commands::version();
  else if (command == "create")
    result = commands::create(arguments, flags);
  else if (command == "test")
    result = commands::test(arguments, flags);
  else if (command == "fpair")
    result = commands::file_pair(arguments, flags);
  else if (command == "class")
    result = commands::class_file_pair(arguments, flags);
  else if (command == "struct")
    result = commands::struct_file_pair(arguments, flags);
  else if (command == "config")
    result = commands::config(arguments, flags);

  /* Saving data */
  if (result == 0 && command != "help" && command != "version")
    data_handler.write();

  /* Artifact cleanup */
  directory::destroy_file("cpm.tmp");

  /* Success message + time measurement */
  const auto end = std::chrono::high_resolution_clock::now();

  logger.custom(
      "command \'" + command + "\' with exit code " + std::to_string(result) +
          " in " +
          std::to_string(
              std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                  .count()) +
          " ms",
      "finished", "theme");
  logger.flush_buffer();

  return result;
}