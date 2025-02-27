/**
 * @file command.cpp
 * @brief Defines static singletons
 * @version 0.1
 * @date 2025-02-23
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "../../include/commands/command.h"

Logger &Command::logger = Logger::get();
Data_Manager &Command::data_manager = Data_Manager::get();