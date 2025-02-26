/**
 * @file config_command.cpp
 * @brief Adds functionality to config command
 * @version 0.1
 * @date 2025-02-23
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "commands/config_command.h"
#include "data.h"
#include "logger.h"

/**
 * @brief Construct a new Config_Command object
 *
 */
Config_Command::Config_Command() {}

/**
 * @brief Execute config command
 *
 * @param args
 * @param flags
 * @return uint8_t
 */
uint8_t Config_Command::execute(const std::vector<std::string>& args,
                                const std::vector<std::string>& flags) const {
  if (args[0] == "set") {
    if (args.size() < 3) {
      logger.error_q("sub-command requires at least 3 arguments", "set");
      return 1;
    }

    data_manager.config[args[1]] = args[2];
    logger.success_q("set to '" + args[2] + "'", args[1]);
  } else if (args[0] == "remove") {
    data_manager.config.erase(args[1]);
    logger.success_q("removed from config", args[1]);
  } else {
    logger.error_q("sub-command is not valid", args[0]);
    return 1;
  }

  return 0;
}

/**
 * @brief Gets description of command
 *
 * @return std::string
 */
std::string Config_Command::get_description() const {
  return "Allows access to configuration variables of CPM";
}

/**
 * @brief Gets command arguments
 *
 * @return std::string
 */
std::string Config_Command::get_arguments() const {
  return "[sub command] sub command of config to execute\t[key] configuration "
         "key to use\t[value] (only required for set sub command) value to set "
         "key to";
}

/**
 * @brief Gets command flags
 *
 * @return std::string
 */
std::string Config_Command::get_flags() const { return "None"; }

/**
 * @brief Gets minimum arguments
 *
 * @return uint16_t
 */
uint16_t Config_Command::get_min_args() const { return 2; }