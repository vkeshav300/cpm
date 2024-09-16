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
#include "misc.h"
#include <chrono>
#include <map>
#include <string>
#include <vector>

std::map<std::string, std::map<std::string, int>> command_info = {
    {
        "create",
        {
            {"init_exception", true},
            {"min_args", 1},
        },
    },
    {
        "help",
        {
            {"init_exception", true},
            {"min_args", 0},
        },
    },
    {
        "version",
        {
            {"init_exception", true},
            {"min_args", 0},
        },
    },
    {
        "test",
        {
            {"init_exception", true},
            {"min_args", 0},
        },
    },
};

/**
 * @brief Processes command.
 *
 * @param command
 * @param arguments
 * @param flags
 * @param language
 * @return int
 */
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

  logger.set_colors({
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
  });

  // Verifies command is inputted
  if (argc <= 1)
  {
    logger.error("no command provided");
    logger.flush_buffer();

    return 1;
  }

  // Parses command & converts argv into vectors of arguments and flags
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

  if (not command_found)
  {
    logger.error_q("is not a valid command", command);
    return 1;
  }

  std::vector<std::string> arguments;
  std::vector<std::string> flags;

  // Flags
  for (int i = 0; i < argc; i++)
  {
    std::string arg = argv[i];
    if ("-" == arg.substr(0, 1) && arg.size() >= 2)
      flags.push_back(arg.substr(1, arg.size()));
  }

  // Arguments
  for (int i = 2; i < argc; i++)
  {
    std::string arg = argv[i];
    if (arg.substr(0, 1) != "-")
      arguments.push_back(arg);
  }

  logger.success("parsed command");

  // Minimum arguments
  if (arguments.size() < command_info[command]["min_args"])
  {
    logger.error_q("requires more than " + std::to_string(arguments.size()) + " arguments", command);
  }

  // Command processing
  int result = 0;

  if (command == "help")
    result = commands::help();
  else if (command == "version")
    result = commands::version();
  else if (command == "create")
    result = commands::create(arguments);

  // Measure process time
  auto end = std::chrono::high_resolution_clock::now();

  logger.custom("command \'" + command + "\' with exit code " + std::to_string(result) + " in " + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) + " ms", "finished", "blue");
  logger.flush_buffer();

  return result;
}