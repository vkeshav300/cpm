#pragma once

#include "../data.h"
#include "../logger.h"

#include <cstdint>
#include <string>
#include <vector>

class Command {
protected:
  static Logger &logger;
  static Data_Manager &data_manager;

public:
  virtual ~Command() = default;

  virtual uint8_t execute(const std::vector<std::string> &args,
                          const std::vector<std::string> &flags) const = 0;
  virtual std::string get_description() const = 0;
  virtual std::string get_arguments() const = 0;
  virtual std::string get_flags() const = 0;
  virtual uint16_t get_min_args() const = 0;
};
