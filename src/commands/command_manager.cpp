/**
 * @file command_manager.cpp
 * @brief Adds functionality to command manager class
 * @version 0.1
 * @date 2025-02-23
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "commands/command_manager.h"
#include "logger.h"
#include "misc.h"

#include <iostream>

Logger& logger = Logger::get();

/**
 * @brief Registers command
 *
 * @param name
 * @param command
 */
void Command_Manager::register_command(const std::string& name,
                                       std::unique_ptr<Command> command) {
  commands[name] = std::move(command);
}

/**
 * @brief Checks if command has been registered
 *
 * @param name
 * @return true
 * @return false
 */
bool Command_Manager::exists(const std::string& name) const {
  if (commands.find(name) == commands.end())
    return false;

  return true;
}

/**
 * @brief Executes command
 *
 * @param name
 * @param args
 * @param flags
 * @return uint8_t
 */
uint8_t Command_Manager::execute(const std::string& name,
                                 const std::vector<std::string>& args,
                                 const std::vector<std::string>& flags) const {
  auto cmd = commands.find(name);

  if (cmd == commands.end()) {
    logger.error_q("is not a registered command, try using cpm --help for "
                   "command information",
                   name);
    return 1;
  }

  return cmd->second->execute(args, flags);
}

/**
 * @brief Gets minimum number of arguments for command
 *
 * @param name Command name
 * @return uint16_t
 */
uint16_t Command_Manager::get_min_args(const std::string& name) const {
  auto cmd = commands.find(name);

  return cmd->second->get_min_args();
}

/**
 * @brief Displays help menu
 *
 * @param args
 * @return uint8_t
 */
uint8_t Command_Manager::help_menu(const std::vector<std::string>& args) const {
  if (args.empty()) {
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
    std::cout << "\n" << logger.colors["theme"];
    for (const auto& [name, cmd] : commands)
      std::cout << name << " command:\n"
                << "\targuments: " << cmd->get_arguments()
                << "\n\tflags: " << cmd->get_flags()
                << "\n\tminimum arguments: "
                << std::to_string(cmd->get_min_args()) << "\n\n";

    std::cout << logger.colors["reset"];
  } else {
    auto cmd = commands.find(args[0]);

    if (cmd == commands.end()) {
      logger.error_q(
          "does not have any registered information, try using cpm --help",
          args[0]);
      return 1;
    }

    std::cout << logger.colors["theme"] << cmd->first << " command:\n"
              << "description: " << cmd->second->get_description()
              << "\narguments:\n\t";

    std::string cout_str(cmd->second->get_arguments());
    misc::replace_string_instances(cout_str, "\t", "\n\t");
    std::cout << cout_str;

    cout_str = cmd->second->get_flags();
    misc::replace_string_instances(cout_str, "\t", "\n\t");
    std::cout << "\n\nflags:\n\t" << cout_str << "\n\nminimum arguments: "
              << std::to_string(cmd->second->get_min_args()) << "\n\n"
              << logger.colors["reset"];
  }

  std::cout << "universal flags (work with any command they apply to):\n"
            << "\t--hpp use .hpp header files instead of .h header files\n"
            << "\n";

  return 0;
}