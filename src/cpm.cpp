/**
 * @file main.cpp
 * @brief Puts together all the other files.
 * @version 0.1
 * @date 2023-09-29
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "commands.h"
#include "cpm_store.h"
#include "directory.h"
#include "logger.h"
#include "misc.h"
#include <algorithm>
#include <chrono>
#include <curl/curl.h>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

std::map<std::string, std::map<std::string, int>> command_info = {
    {
        "init",
        {
            {"init_exception", 1},
            {"first_arg_lang", 1},
            {"min_args", 1},
        },
    },
    {
        "pair",
        {
            {"init_exception", 0},
            {"first_arg_lang", 0},
            {"min_args", 2},
        },
    },
    {
        "help",
        {
            {"init_exception", 1},
            {"first_arg_lang", 0},
            {"min_args", 0},
        },
    },
    {
        "version",
        {
            {"init_exception", 1},
            {"first_arg_lang", 0},
            {"min_args", 0},
        },
    },
    {
        "contents",
        {
            {"init_exception", 1},
            {"first_arg_lang", 0},
            {"min_args", 2},
        },
    },
    {
        "install",
        {
            {"init_exception", 0},
            {"first_arg_lang", 0},
            {"min_args", 1},
        },
    },
    {
        "uninstall",
        {
            {"init_exception", 0},
            {"first_arg_lang", 0},
            {"min_args", 1},
        },
    },
    {
        "test",
        {
            {"init_exception", 1},
            {"first_arg_lang", 0},
            {"min_args", 0},
        },
    },
};

/**
 * @brief Processes command.
 *
 * @param command
 * @param arguments
 * @param flags
 * @param language
 * @return int
 */
int process_command(std::string command, std::vector<std::string> arguments,
                    std::vector<std::string> flags, std::string language) {
  int r_code = 1;

  if ("init" == command) {
    if (misc::find_in_vector(flags, "post")) {
      r_code = commands::post_init(language);
      return r_code;
    }

    r_code = commands::init(language, flags);
  } else if ("pair" == command)
    r_code = commands::file_pair(
        arguments, (misc::find_in_vector(flags, "hpp")) ? true : false,
        language);
  else if ("help" == command)
    r_code = commands::help();
  else if ("version" == command)
    r_code = commands::version();
  else if ("contents" == command)
    r_code = commands::contents(arguments, flags);
  else if ("install" == command)
    r_code = commands::install(arguments, flags, language);
  else if ("uninstall" == command)
    r_code = commands::uninstall(arguments);
  else if ("test" == command) {
  }

  return r_code;
}

/**
 * @brief Main function.
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char *argv[]) {
  auto start = std::chrono::high_resolution_clock::now();

  if (argc <= 1) {
    logger::error("no command provided");
    logger::flush_buffer();

    return 1;
  }

  std::string command = argv[1];
  std::vector<std::string> arguments;
  std::vector<std::string> flags;

  for (int i = 0; i < argc; i++) {
    std::string arg = argv[i];
    if ("-" == arg.substr(0, 1) && arg.size() >= 2)
      flags.push_back(arg.substr(1, arg.size()));
  }

  for (int i = 2; i < argc; i++) {
    std::string arg = argv[i];
    if (arg.substr(0, 1) != "-")
      arguments.push_back(arg);
  }

  logger::success("parsed command");

  if ("--version" == command)
    command = "version";

  if (!command_info.count(command)) {
    logger::error_q("is not a valid command", command);
    logger::flush_buffer();

    return 1;
  }

  bool initialized = commands::verify_init();
  bool command_is_exception = false;

  if (true == command_info[command]["init_exception"])
    command_is_exception = true;

  std::string language;

  if (initialized) {
    const std::map<std::string, std::string> cpm_file =
        directory::parse_cpm("./", ".cpm");

    if (!cpm_file.count("language")) {
      logger::error("directory contains invalid .cpm file");

      return 1;
    }

    try {
      language = cpm_file.at("language");
    } catch (const std::out_of_range &e) {
      logger::error(e.what());
      return 1;
    }
  } else if (true == command_info[command]["first_arg_lang"])
    language = arguments[0];
  else if (command_is_exception)
    language = "c"; // ? Placeholder - doesn't actually matter
  else {
    logger::warn(
        "directory must be initialized with cpm (use cpm help for more info)");
    logger::flush_buffer();

    return 1;
  }

  if ("c++" == language)
    language = "cpp";

  if ("c" != language && "cpp" != language) {
    logger::error("invalid language provided");
    return 1;
  }

  logger::custom("command \'" + command + "\' with " +
                     std::to_string(arguments.size()) + " argument(s) and " +
                     std::to_string(flags.size()) + " flag(s)",
                 "received", "blue");

  if (arguments.size() < command_info[command]["min_args"]) {
    logger::error("minimum amount of arguments not met");
    return 1;
  }

  logger::success(language);

  curl_global_init(CURL_GLOBAL_DEFAULT);

  int result = process_command(command, arguments, flags, language);

  curl_global_cleanup();

  auto end = std::chrono::high_resolution_clock::now();

  logger::custom(
      "command \'" + command + "\' with exit code " + std::to_string(result) +
          " in " +
          std::to_string(
              std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                  .count()) +
          " ms",
      "finished", "blue");
  logger::flush_buffer();

  return 0;
}
