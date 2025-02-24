/**
 * @file help_command.cpp
 * @brief Adds functionality to help command
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "commands/help_command.h"
#include "logger.h"

#include <iostream>

/**
 * @brief Construct a new Help_Command object
 * 
 */
Help_Command::Help_Command() {}

/**
 * @brief Execute help command
 * 
 * @param args 
 * @param flags 
 * @return uint8_t 
 */
uint8_t Help_Command::execute(const std::vector<std::string> &args,
                              const std::vector<std::string> &flags) const {
  /* ASCII art */
  std::cout << "\n"
            << logger.colors["theme"]
            << "      ___           ___         ___     \n"
            << "     /  /\\         /  /\\       /__/\\    \n"
            << "    /  /:/        /  /::\\     |  |::\\   \n"
            << "   /  /:/        /  /:/\\:\\    |  |:|:\\  \n"
            << "  /  /:/  ___   /  /:/~/:/  __|__|:|\\:\\ \n"
            << " /__/:/  /  /\\ /__/:/ /:/  /__/::::| \\:\\\n"
            << " \\  \\:\\ /  /:/ \\  \\:\\/:/   \\  \\:\\~~\\__\\/\n"
            << "  \\  \\:\\  /:/   \\  \\::/     \\  \\:\\      \n"
            << "   \\  \\:\\/:/     \\  \\:\\      \\  \\:\\     \n"
            << "    \\  \\::/       \\  \\:\\      \\  \\:\\    \n"
            << "     \\__\\/         \\__\\/       \\__\\/    \n\n\n"
            << logger.colors["reset"];

  logger.custom("https://github.com/vkeshav300/cpm", "github page", "theme");
  logger.custom("https://github.com/vkeshav300/cpm/wiki", "general wiki",
                "theme");
  logger.custom("https://github.com/vkeshav300/cpm/wiki/Commands",
                "commands documentation", "theme");
  logger.custom("https://github.com/vkeshav300/cpm/releases/latest",
                "latest release", "theme");
  std::cout << "\n";

  return 0;
}

/**
 * @brief Gets description of command
 * 
 * @return std::string 
 */
std::string Help_Command::get_description() const {
  return "Logs useful information about CPM";
}

/**
 * @brief Gets command arguments
 * 
 * @return std::string 
 */
std::string Help_Command::get_arguments() const { return ""; }

/**
 * @brief Gets command flags
 * 
 * @return std::string 
 */
std::string Help_Command::get_flags() const { return ""; }

/**
 * @brief Gets minimum arguments
 * 
 * @return uint16_t 
 */
uint16_t Help_Command::get_min_args() const { return 0; }