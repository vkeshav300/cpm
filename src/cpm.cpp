/**
 * @file main.cpp
 * @brief Puts together all the other files.
 * @version 0.1
 * @date 2023-09-29
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "commands.h"
#include "directory.h"
#include "logger.h"
#include "data.h"

#include <chrono>
#include <unordered_map>
#include <string>
#include <vector>

std::unordered_map<std::string, std::unordered_map<std::string, int>> command_info = {
    {
        "create",
        {
            {"min_args", 1},
        },
    },
    {
        "help",
        {
            {"min_args", 0},
        },
    },
    {
        "version",
        {
            {"min_args", 0},
        },
    },
    {
        "test",
        {
            {"min_args", 0},
        },
    },
    {
        "fpair",
        {
            {"min_args", 2},
        },
    },
    {
        "class",
        {
            {"min_args", 1},
        },
    },
    {
        "config",
        {
            {"min_args", 2},
        },
    },
};
/**
 * @brief Main function.
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char *argv[])
{
  // Start time
  auto start = std::chrono::high_resolution_clock::now();

  // Singleton accessing
  Logger &logger = Logger::get();
  Data_Handler &data_handler = Data_Handler::get();

  data_handler.read();

  // Overwrites existing colormap with user preferences
  for (const auto &[k, v] : logger.colors)
  {
    if (data_handler.config_has_key("color_" + k))
      logger.set_color(k, logger.raw_colors[data_handler.config["color_" + k]]);
  }

  // Verifies command is inputted
  if (argc <= 1)
  {
    logger.error("no command provided");
    logger.flush_buffer();

    return 1;
  }

  // Initial validations
  std::string command = argv[1];
  bool command_found = false;

  // Checks if command is valid
  for (const auto &[k, v] : command_info)
  {
    if (k == command)
    {
      command_found = true;
      break;
    }
  }

  // Checks if command exists
  if (!command_found)
  {
    logger.error_q("is not a valid command", command);
    return 1;
  }

  // Parsing
  std::vector<std::string> arguments;
  std::vector<std::string> flags;

  // Flags
  for (int i = 0; i < argc; i++)
  {
    std::string arg = argv[i];
    if (arg[0] == '-' && arg.size() > 1)
    {
      if (arg[1] == '-' && arg.size() > 2) // --flag
      {
        flags.push_back(arg.substr(2, arg.size()));
        continue;
      }

      flags.push_back(arg.substr(1, arg.size())); // -f
    }
  }

  // Arguments
  for (int i = 2; i < argc; i++)
  {
    std::string arg = argv[i];
    if (arg[0] != '-')
      arguments.push_back(arg);
  }

  logger.success("parsed command");

  // Minimum arguments
  if (arguments.size() < command_info[command]["min_args"])
  {
    logger.error_q("requires at least " + std::to_string(command_info[command]["min_args"]) + " arguments", command);
    return 1;
  }

  // Command processing
  int result = 0;

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
  else if (command == "config")
    result = commands::config(arguments, flags);

  // Save data
  if (result == 0 && command != "help" && command != "version")
    data_handler.write();

  // Cleanup artifacts
  directory::destroy_file("cpm.tmp");

  // Measure process time
  auto end = std::chrono::high_resolution_clock::now();

  logger.custom("command \'" + command + "\' with exit code " + std::to_string(result) + " in " + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) + " ms", "finished", "theme");
  logger.flush_buffer();

  return result;
}