/**
 * @file scan_command.cpp
 * @brief Implements scan command
 * @version 0.1
 * @date 2025-02-27
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "commands/scan_command.h"

#include "config.h"
#include "data.h"
#include "misc.h"
#include "updates.h"

/**
 * @brief Construct a new Scan_Command object
 *
 */
Scan_Command::Scan_Command() {}

/*
## Update Summary
Auto-update scanning (checks for updates automatically) has been implemented
with this version. There may be lag, so if you don't care about scanning for
updates automatically, run:
```
cpm config set update_scanning off
```
to disable automatic update scanning, and remove any associated lag.
*/

/**
 * @brief Execute scan command
 *
 * @param args
 * @param flags
 * @return uint8_t
 */
uint8_t Scan_Command::execute(const std::vector<std::string> &args,
                              const std::vector<std::string> &flags) const {
  if (flags.size() > 0 && flags[0] == "off") {
    data_manager.config["auto_usc"] = "off";
    logger.success(
        "disabled automatic update scanning (to enable run: cpm scan --on)");
    return 0;
  } else if (flags.size() > 0 && flags[0] == "on") {
    data_manager.config["auto_usc"] = "on";
    logger.success(
        "enabled automatic update scanning (to disable run: cpm scan --off)");
    return 0;
  }

  if ((!data_manager.config_has_key("auto_usc") ||
       data_manager.config["auto_usc"] != "off") &
      (flags.size() > 0 && flags[0][0] == 'f')) {
    uint16_t frequency;

    if (!misc::string_to_uint16(misc::get_flag_value(flags[0]), frequency) || frequency == 0) {
      logger.error("invalid scan frequency (must be positive integer greater than 1)");
      return 1;
    }

    data_manager.config["auto_usc_freq"] = std::to_string(frequency);
    data_manager.config["runs_since_last_scan"] = std::to_string(frequency);

    logger.success("updates will now scan every " + std::to_string(frequency) +
                   " command runs");

    return 0;
  }

  logger.success("scanning for updates (current version v" +
                 std::string(version_string) + ")");

  const uint8_t result = updates::scan();

  if (result == 0)
    logger.custom("no updates found", "updates", "theme");
  else if (result == 1)
    return 0;

  return result;
}

/**
 * @brief Get description for scan command
 *
 * @return std::string
 */
std::string Scan_Command::get_description() const {
  return "scans for updates to CPM";
}

/**
 * @brief Get arguments for scan command
 *
 * @return std::string
 */
std::string Scan_Command::get_arguments() const { return "None"; }

/**
 * @brief Get flags for scan command
 *
 * @return std::string
 */
std::string Scan_Command::get_flags() const {
  return "-f=[n] set automatic update scanning to run every n commands\t--off "
         "disable automatic update scanning\t--on enable automatic update "
         "scanning";
}

/**
 * @brief Get minimum arguments for scan command
 *
 * @return uint16_t
 */
uint16_t Scan_Command::get_min_args() const { return 0; };