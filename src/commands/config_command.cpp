#include "commands/config_command.h"
#include "data.h"
#include "logger.h"

Config_Command::Config_Command() {}

uint8_t Config_Command::execute(const std::vector<std::string> &args,
                                const std::vector<std::string> &flags) const {
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

std::string Config_Command::get_description() const {
  return "Allows access to configuration variables of CPM";
}

std::string Config_Command::get_arguments() const { return ""; }

std::string Config_Command::get_flags() const { return ""; }

uint16_t Config_Command::get_min_args() const { return 2; }