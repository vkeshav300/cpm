#include "commands/version_command.h"

#include "../config.h"

Version_Command::Version_Command() {}

uint8_t Version_Command::execute(const std::vector<std::string> &args,
                                 const std::vector<std::string> &flags) const {
  logger.custom(version_string, "version", "theme");
  return 0;
}

std::string Version_Command::get_description() const {
  return "Logs installed version of CPM";
}

std::string Version_Command::get_arguments() const { return ""; }

std::string Version_Command::get_flags() const { return ""; }

uint16_t Version_Command::get_min_args() const { return 0; }