#include "commands/help_command.h"
#include "logger.h"

#include <iostream>

Help_Command::Help_Command() {}

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

std::string Help_Command::get_description() const {
  return "Logs useful information about CPM";
}

std::string Help_Command::get_arguments() const { return ""; }

std::string Help_Command::get_flags() const { return ""; }

uint16_t Help_Command::get_min_args() const { return 0; }