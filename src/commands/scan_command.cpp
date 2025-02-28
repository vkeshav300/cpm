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

#include "updates.h"
#include "config.h"

/**
 * @brief Construct a new Scan_Command object
 * 
 */
Scan_Command::Scan_Command() {}

/*
## Update Summary
Auto-update scanning (checks for updates automatically) has been implemented with this version. There may be lag, so if you don't care about scanning for updates automatically, run:
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
uint8_t Scan_Command::execute(const std::vector<std::string> &args, const std::vector<std::string> &flags) const {
    logger.success("scanning for updates (current version v" + std::string(version_string) + ")");

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
std::string Scan_Command::get_arguments() const {
    return "None";
}

/**
 * @brief Get flags for scan command
 * 
 * @return std::string 
 */
std::string Scan_Command::get_flags() const {
    return "None";
}

/**
 * @brief Get minimum arguments for scan command
 * 
 * @return uint16_t 
 */
uint16_t Scan_Command::get_min_args() const {
    return 0;
};