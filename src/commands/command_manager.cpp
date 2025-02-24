#include "commands/command_manager.h"
#include "logger.h"

void Command_Manager::register_command(const std::string &name,
                                       std::unique_ptr<Command> command) {
  commands[name] = std::move(command);
}

bool Command_Manager::exists(const std::string &name) const {
  if (commands.find(name) == commands.end())
    return false;

  return true;
}

uint8_t Command_Manager::execute(const std::string &name,
                                 const std::vector<std::string> &args,
                                 const std::vector<std::string> &flags) const {
  auto cmd = commands.find(name);

  if (cmd == commands.end()) {
    Logger::get().error_q("is not a registered command", name);
    return 1;
  }

  return cmd->second->execute(args, flags);
}

uint16_t Command_Manager::get_min_args(const std::string &name) const {
  auto cmd = commands.find(name);

  return cmd->second->get_min_args();
}