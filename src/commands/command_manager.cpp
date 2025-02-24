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

/**
 * @brief Registers command
 * 
 * @param name 
 * @param command 
 */
void Command_Manager::register_command(const std::string &name,
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
bool Command_Manager::exists(const std::string &name) const {
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

/**
 * @brief Gets minimum number of arguments for command
 * 
 * @param name Command name
 * @return uint16_t 
 */
uint16_t Command_Manager::get_min_args(const std::string &name) const {
  auto cmd = commands.find(name);

  return cmd->second->get_min_args();
}