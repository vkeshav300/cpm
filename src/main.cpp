/**
 * @file main.cpp
 * @brief Main file
 * @version 0.1
 * @date 2023-09-29
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "../include/data.h"
#include "../include/directory.h"
#include "../include/logger.h"
#include "../include/misc.h"

#include "../include/commands/class_command.h"
#include "../include/commands/command_manager.h"
#include "../include/commands/config_command.h"
#include "../include/commands/fpair_command.h"
#include "../include/commands/init_command.h"
#include "../include/commands/struct_command.h"
#include "../include/commands/version_command.h"

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
  Data_Manager &data_manager = Data_Manager::get();

  data_manager.read();

  /* Overwrites colormap with config variables */
  if (data_manager.config_has_key("text_coloring") &&
      data_manager.config["text_coloring"] == "off") {
    logger.disable_coloring();
  } else {
    for (const auto &[k, v] : logger.colors) {
      if (data_manager.config_has_key("color_" + k))
        logger.set_color(k,
                         logger.raw_colors[data_manager.config["color_" + k]]);
    }
  }

  /* Register commands */
  Command_Manager manager;
  manager.register_command("class", std::make_unique<Class_Command>());
  manager.register_command("config", std::make_unique<Config_Command>());
  manager.register_command("fpair", std::make_unique<Fpair_Command>());
  manager.register_command("init", std::make_unique<Init_Command>());
  manager.register_command("struct", std::make_unique<Struct_Command>());
  manager.register_command("version", std::make_unique<Version_Command>());

  /* Checks if command was inputted */
  if (argc <= 1) {
    logger.error("no command provided");
    logger.flush_buffer();

    return 1;
  }

  /* Parsing */
  const std::string cmd = argv[1];
  if (!manager.exists(cmd) & cmd != "--help") {
    logger.error_q("command does not exist, try using cpm --help", cmd);
    return 1;
  }

  std::vector<std::string> args;
  std::vector<std::string> flags;

  /* Flags */
  for (int i = 0; i < argc; i++) {
    std::string arg = argv[i];
    if (arg[0] == '-' & arg.size() > 1) {
      uint8_t _start = 1; // -f
      if (arg[1] == '-' & arg.size() > 2)
        _start = 2; // --flag

      flags.push_back(arg.substr(_start, arg.size()));
    }
  }

  /* Arguments */
  for (int i = 2; i < argc; i++) {
    std::string arg = argv[i];
    if (arg[0] != '-')
      args.push_back(arg);
  }

  logger.success("parsed command");

  /* Determines if help menu needs to be displayed */
  const bool help_menu = misc::vector_contains(flags, "help");

  /* Checks if minimum arguments requirement is met */
  if (!help_menu) {
    const uint16_t cmd_min_args = manager.get_min_args(cmd);
    if (args.size() < cmd_min_args) {
      logger.error_q("requires at least " + std::to_string(cmd_min_args) +
                         " arguments",
                     cmd);
      return 1;
    }
  }

  /* Command execution */
  uint8_t result;
  if (help_menu) {
    if (cmd != "--help") {
      if (args.empty())
        args.push_back(cmd);
      else
        args[0] = cmd;
    }

    result = manager.help_menu(args);
  }

  else
    result = manager.execute(cmd, args, flags);

  /* Saving data */
  if ((result == 0) & (cmd != "--help") & (cmd != "version"))
    data_manager.write();

  /* Artifact cleanup */
  directory::destroy_file("cpm.tmp");

  /* Success message + time measurement */
  const auto end = std::chrono::high_resolution_clock::now();

  logger.custom(
      "command \'" + cmd + "\' with exit code " + std::to_string(result) +
          " in " +
          std::to_string(
              std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                  .count()) +
          " ms",
      "finished", "theme");
  logger.flush_buffer();

  return result;
}