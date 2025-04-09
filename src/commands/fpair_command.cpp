/**
 * @file fpair_command.cpp
 * @brief Adds functionality to fpair command
 * @version 0.1
 * @date 2025-02-23
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "commands/fpair_command.h"

#include "directory.h"
#include "file.h"
#include "misc.h"

/**
 * @brief Construct a new Fpair_Command object
 *
 */
Fpair_Command::Fpair_Command() {}

/**
 * @brief Execute fpair command
 *
 * @param args
 * @param flags
 * @return uint8_t
 */
uint8_t Fpair_Command::execute(const std::vector<std::string> &args,
                               const std::vector<std::string> &flags) const {
  /* Determines path prefixes */
  for (const auto &arg :
       misc::sub_vector<std::string>(args, 1, args.size() - 1)) {
    if (args[0] == "create") {
      const std::filesystem::path header_path(
          directory::get_structured_header_path(
              arg, (misc::vector_contains(flags, "hpp")))),
          source_path(directory::get_structured_source_path(arg));
      std::filesystem::path source_include_path;

      File header(header_path);
      header.load({"#pragma once"});

      if (source_path.parent_path() == header_path.parent_path())
        source_include_path = header_path.stem();
      else
        source_include_path = arg;

      File source(source_path);
      source.load({"#include \"" + source_include_path.string() +
                   (misc::vector_contains(flags, "hpp") ? ".hpp" : ".h") +
                   "\""});
    } else if (args[0] == "remove") {
      directory::destroy_file("include/" + arg + ".h");
      directory::destroy_file("include/" + arg + ".hpp");
      directory::destroy_file("src/" + arg + ".c");
      directory::destroy_file("src/" + arg + ".cpp");
      directory::destroy_file(arg + ".h");
      directory::destroy_file(arg + ".hpp");
      directory::destroy_file(arg + ".c");
      directory::destroy_file(arg + ".cpp");
    } else {
      logger.error_q("is an invalid sub-command", args[0]);
      return 1;
    }
  }

  return 0;
}

std::string Fpair_Command::get_description() const {
  return "Creates a header-source file pair";
}

std::string Fpair_Command::get_arguments() const {
  return "[sub command] sub command of fpair to execute\t[file names] names of "
         "file pairs to create (separated by spaces)";
}

std::string Fpair_Command::get_flags() const { return "None"; }

uint16_t Fpair_Command::get_min_args() const { return 2; }
