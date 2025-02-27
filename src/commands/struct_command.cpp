/**
 * @file struct_command.cpp
 * @brief Adds functionality to struct command
 * @version 0.1
 * @date 2025-02-23
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "../../include/commands/struct_command.h"
#include "../../include/commands/fpair_command.h"

#include "../../include/directory.h"
#include "../../include/file.h"
#include "../../include/misc.h"

#include <filesystem>

/**
 * @brief Construct a new Struct_Command object
 *
 */
Struct_Command::Struct_Command() {}

/**
 * @brief Execute struct command
 *
 * @param args
 * @param flags
 * @return uint8_t
 */
uint8_t Struct_Command::execute(const std::vector<std::string> &args,
                                const std::vector<std::string> &flags) const {
  /* Create file pairs */
  std::vector<std::string> file_pair_args(args);
  file_pair_args.insert(file_pair_args.begin(), "create");

  Fpair_Command fpair_command;
  const uint8_t result = fpair_command.execute(file_pair_args, flags);

  if (result != 0)
    return result;

  /* Open files */
  std::string struct_name, _struct_name;

  for (const auto &arg : args) {
    /* Open and write to files */
    std::filesystem::path _arg(arg);

    _struct_name = std::filesystem::absolute(_arg).filename().string();
    misc::auto_capitalize(struct_name = _struct_name);

    File header(directory::get_structured_header_path(
        arg, misc::vector_contains(flags, "hpp"))),
        source(directory::get_structured_source_path(arg));

    if (!misc::vector_contains(flags, "ntypedef")) {
      header.write({"typedef struct {", "\t", "} " + struct_name + ";", "",
                    struct_name + " *create_" + _struct_name + "();"});

      source.write(
          {struct_name + " *create_" + _struct_name + "() {", "\t", "}"});
    } else {
      header.write({
          "struct " + struct_name + " {",
          "",
          "}",
          "",
          "struct " + struct_name + " *create_" + _struct_name + "();",
      });

      source.write({
          "struct " + struct_name + " *create_" + _struct_name + "() {",
          "",
          "}",
      });
    }
  }

  return 0;
}

/**
 * @brief Gets description of command
 *
 * @return std::string
 */
std::string Struct_Command::get_description() const {
  return "Creates a struct based header-source file pair";
}

/**
 * @brief Gets command arguments
 *
 * @return std::string
 */
std::string Struct_Command::get_arguments() const {
  return "[names] names of files that will contain structs";
}

/**
 * @brief Gets command flags
 *
 * @return std::string
 */
std::string Struct_Command::get_flags() const {
  return "--ntypedef don't use typedef keyword";
}

/**
 * @brief Gets minimum arguments
 *
 * @return uint16_t
 */
uint16_t Struct_Command::get_min_args() const { return 1; }