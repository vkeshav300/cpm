#pragma once

#include "command.h"

#include <cstdint>
#include <string>
#include <vector>

class Config_Command : public Command {
public:
  Config_Command();

  uint8_t execute(const std::vector<std::string> &args,
                  const std::vector<std::string> &flags) const override;
  std::string get_description() const override;
  std::string get_arguments() const override;
  std::string get_flags() const override;
  uint16_t get_min_args() const override;
};