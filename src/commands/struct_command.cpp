/**
 * @file struct_command.cpp
 * @brief Adds functionality to struct command
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "commands/struct_command.h"
#include "commands/fpair_command.h"

#include "directory.h"
#include "file.h"
#include "misc.h"

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
  std::string prefix_a, struct_name;
  bool status = false;
  std::vector<std::string> split_arg;

  for (const auto &arg : args) {
    /* Code commenting similar to class_file_pair */
    std::filesystem::path _arg(arg);
    struct_name = std::filesystem::absolute(_arg).filename().string();
    misc::auto_capitalize(struct_name);

    prefix_a = struct_name + "::";

    File header(directory::get_structured_header_path(
        arg, misc::vector_contains(flags, "hpp"))),
        source(directory::get_structured_source_path(arg));

    if (flags.size() > 0 && flags[0][0] == 'p') {
      _arg = misc::get_flag_value(flags[0]);
      const std::filesystem::path header_p_path(
          std::filesystem::absolute(directory::get_structured_header_path(
              _arg, !directory::has_file(
                        directory::get_structured_header_path(_arg)))));

      if (!directory::has_file(header_p_path)) {
        logger.error_q("does not exist", header_p_path);
        return 1;
      }

      File header_p(header_p_path);

      prefix_a = _arg.filename().string();
      misc::auto_capitalize(prefix_a);

      /* Auto relative path detection (between parent header and child
       * header)
       */
      std::string include_path = "";
      misc::set_relative_path(include_path, header.get_path(),
                              header_p.get_path());

      header.write({
          "#include \"" + include_path + "\"",
          "",
          "struct " + struct_name + " {",
          "\t" + struct_name + "();",
          "\t~" + struct_name + "();",
          "};",
      });

      prefix_a = struct_name + "::";

      source.write({
          prefix_a + struct_name + "() {}",
          prefix_a + "~" + struct_name + "() {}",
      });
    } else {
      header.write({
          "struct " + struct_name + " {",
          "\t" + struct_name + "();",
          "\t~" + struct_name + "();",
          "};",
      });

      source.write({
          prefix_a + struct_name + "() {}",
          prefix_a + "~" + struct_name + "() {}",
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
std::string Struct_Command::get_arguments() const { return ""; }

/**
 * @brief Gets command flags
 * 
 * @return std::string 
 */
std::string Struct_Command::get_flags() const { return ""; }

/**
 * @brief Gets minimum arguments
 * 
 * @return uint16_t 
 */
uint16_t Struct_Command::get_min_args() const { return 1; }