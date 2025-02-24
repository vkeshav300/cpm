/**
 * @file class_command.cpp
 * @brief Adds functionality to class command
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "commands/class_command.h"
#include "commands/fpair_command.h"

#include "directory.h"
#include "file.h"
#include "logger.h"
#include "misc.h"

#include <filesystem>

/**
 * @brief Construct a new Class_Command object
 * 
 */
Class_Command::Class_Command() {}

/**
 * @brief Execute class command
 * 
 * @param args 
 * @param flags 
 * @return uint8_t 
 */
uint8_t Class_Command::execute(const std::vector<std::string> &args,
                               const std::vector<std::string> &flags) const {
  if (directory::get_extension() == ".c") {
    logger.error("C programming language does not support classes");
    return 1;
  }

  /* Create file pairs */
  std::vector<std::string> file_pair_args;

  if (!misc::vector_contains(flags, "interface")) {
    file_pair_args = args;
    file_pair_args.insert(file_pair_args.begin(), "create");
  } else {
    file_pair_args = {
        "create",
        args[0],
    };
  }

  Fpair_Command fpair_command;
  const uint8_t result = fpair_command.execute(file_pair_args, flags);

  if (result != 0)
    return result;

  /* Open files */
  std::string prefix_a, class_name;
  bool status = false;
  std::vector<std::string> split_arg;

  for (const auto &arg : args) {
    std::filesystem::path _arg(
        arg); // Turn 'arg' into filesystem::path for easier path handling
    class_name = std::filesystem::absolute(_arg).filename().string();
    misc::auto_capitalize(class_name);

    /* Write to files */
    prefix_a = class_name + "::";

    File header(directory::get_structured_header_path(
        arg, misc::vector_contains(flags, "hpp"))),
        source(directory::get_structured_source_path(arg));

    if (misc::vector_contains(flags, "singleton")) {
      header.write({
          "class " + class_name + " {",
          "private:",
          "\t" + class_name + "();",
          "",
          "public:",
          "\t" + class_name + "(const " + class_name + " &obj) = delete;",
          "",
          "\tstatic " + class_name + " &get();",
          "};",
      });

      source.write({
          class_name + " &" + prefix_a + "get() {",
          "\tstatic " + class_name + " obj;",
          "\treturn obj;",
          "}",
      });
    } else if (misc::vector_contains(flags, "interface")) {
      header.write({
          "class " + class_name + " {",
          "private:",
          "",
          "public:",
      });

      /* For interfaces, all arguments after first are treated as virtual
       * functions */
      for (const auto &arg :
           misc::sub_vector<std::string>(args, 1, args.size() - 1))
        header.write({"\tvirtual void " + arg + "() = 0;"});

      header.write({
          "};",
      });

      /* Source file isn't required */
      source.remove();

      return 0;
    } else if (flags.size() > 0 && flags[0][0] == 'p') { // inheritance
      // Set '_arg' to path of parent header file
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

      /* Switch 'private' to 'protected' if 'protected' doesn't already
       * exist inside parent class */
      if (!status && !header_p.exists("protected")) {
        header_p.replace_first_with("private", "protected");
        status = true;
      }

      /* Get parent class name */
      prefix_a = _arg.filename().string();
      misc::auto_capitalize(prefix_a);

      /* Get inherit mode (public, protected, private) */
      std::string inherit_mode = "public ";

      if (misc::vector_contains(flags, "protected"))
        inherit_mode = "protected ";
      else if (misc::vector_contains(flags, "private"))
        inherit_mode = "private ";

      /* Auto relative path detection (between parent header and child
       * header)
       */
      std::string include_path = "";
      misc::set_relative_path(include_path, header.get_path(),
                              header_p.get_path());

      /* Write to files */
      header.write({
          "#include \"" + include_path + "\"",
          "",
          "class " + class_name + ": " + inherit_mode + prefix_a + " {",
          "private:",
          "",
          "public:",
          "\t" + class_name + "();",
          "\t~" + class_name + "();",
          "};",
      });

      prefix_a = class_name + "::";

      source.write({
          prefix_a + class_name + "() {}",
          prefix_a + "~" + class_name + "() {}",
      });
    } else {
      header.write({
          "class " + class_name + " {",
          "private:",
          "",
          "public:",
          "\t" + class_name + "();",
          "\t~" + class_name + "();",
          "};",
      });

      source.write({
          prefix_a + class_name + "() {}",
          prefix_a + "~" + class_name + "() {}",
      });
    }
  }

  return 0;
}

std::string Class_Command::get_description() const {
  return "Creates a class-based header-source file pair with many options";
}

std::string Class_Command::get_arguments() const { return ""; }

std::string Class_Command::get_flags() const { return ""; }

uint16_t Class_Command::get_min_args() const { return 1; }