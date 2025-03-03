/**
 * @file version_command.cpp
 * @brief Adds functionality to version command
 * @version 0.1
 * @date 2025-02-23
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "commands/version_command.h"

#include "config.h"

/**
 * @brief Construct a new Version_Command object
 *
 */
Version_Command::Version_Command() {}

/**
 * @brief Execute version command
 *
 * @param args
 * @param flags
 * @return uint8_t
 */
uint8_t Version_Command::execute(const std::vector<std::string> &args,
                                 const std::vector<std::string> &flags) const {
  logger.custom(version_string, "version", "theme");
  return 0;
}

std::string Version_Command::get_description() const {
  return "Logs installed version of CPM";
}

std::string Version_Command::get_arguments() const { return "None"; }

std::string Version_Command::get_flags() const { return "None"; }

uint16_t Version_Command::get_min_args() const { return 0; }