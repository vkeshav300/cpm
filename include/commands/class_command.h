/**
 * @file class_command.h
 * @brief Outlines command for class
 * @version 0.1
 * @date 2025-02-23
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include "command.h"

#include <cstdint>
#include <string>
#include <vector>

class Class_Command : public Command {
public:
  Class_Command();

  uint8_t execute(const std::vector<std::string> &args,
                  const std::vector<std::string> &flags) const override;
  std::string get_description() const override;
  std::string get_arguments() const override;
  std::string get_flags() const override;
  uint16_t get_min_args() const override;
};