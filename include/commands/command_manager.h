#pragma once

#include "command.h"

#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>

class Command_Manager {
private:
  std::unordered_map<std::string, std::unique_ptr<Command>> commands;

public:
  void register_command(const std::string &name,
                        std::unique_ptr<Command> command);
  bool exists(const std::string &name) const;
  uint8_t execute(const std::string &name, const std::vector<std::string> &args,
                  const std::vector<std::string> &flags) const;
  uint16_t get_min_args(const std::string &name) const;
};