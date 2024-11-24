/**
 * @file commands.cpp
 * @brief Contains the functionality of all commands
 * @version 0.1
 * @date 2023-09-29
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "commands.h"
#include "directory.h"
#include "logger.h"
#include "misc.h"
#include "data.h"
#include "file.h"

#include <fstream>
#include <cstdlib>
#include <iostream>
#include <filesystem>

namespace commands
{
  // Logger
  Logger &logger = Logger::get();
  Data_Handler &data_handler = Data_Handler::get();

  /**
   * @brief All templates supported by the create command
   *
   */
  std::vector<std::string> supported_structures = {
      "executable",
      "simple",
  };

  /**
   * @brief Runs test code for CPM.
   *
   * @param args
   * @param flags
   * @return int
   */
  int test(const std::vector<std::string> &args, const std::vector<std::string> &flags) { return 0; }

  /**
   * @brief Lists all commands and provides useful information about CPM
   *
   * @return int
   */
  int help(const std::vector<std::string> &args)
  {
    // CPM ASCII art
    std::cout << "\n"
              << logger.colors["theme"]
              << "      ___           ___         ___     \n"
              << "     /  /\\         /  /\\       /__/\\    \n"
              << "    /  /:/        /  /::\\     |  |::\\   \n"
              << "   /  /:/        /  /:/\\:\\    |  |:|:\\  \n"
              << "  /  /:/  ___   /  /:/~/:/  __|__|:|\\:\\ \n"
              << " /__/:/  /  /\\ /__/:/ /:/  /__/::::| \\:\\\n"
              << " \\  \\:\\ /  /:/ \\  \\:\\/:/   \\  \\:\\~~\\__\\/\n"
              << "  \\  \\:\\  /:/   \\  \\::/     \\  \\:\\      \n"
              << "   \\  \\:\\/:/     \\  \\:\\      \\  \\:\\     \n"
              << "    \\  \\::/       \\  \\:\\      \\  \\:\\    \n"
              << "     \\__\\/         \\__\\/       \\__\\/    \n\n\n"
              << logger.colors["reset"];

    logger.custom("https://github.com/vkeshav300/cpm\n\n\n", "github", "theme");

    // Specifc command focus
    std::cout << logger.colors["theme"];

    if (args.size() > 0)
    {
      std::string command = args[0];

      if (command == "help")
        std::cout << "help {command} --> gets information related to CPM and it's commands\n"
                  << "  {command} --> specific command to focus information on\n\n"
                  << "Ex: cpm help create";
      else if (command == "version")
        std::cout << "version --> states version of CPM installed\n\n";
      else if (command == "create")
        std::cout << "create [language] --> creates new c/c++ project\n"
                  << "  language --> language project will be based off of, C or C++ (ex. cpp)\n"
                  << "  -v=... --> Specify a specific language verison to use (ex. -v=17)\n\n"
                  << "Different Project Templates:\n"
                  << "  executable --> 'executable' project structure, built around CMake\n"
                  << "  simple   --> only creates one main file in working directory\n\n"
                  << "Ex: cpm create cpp";
      else if (command == "fpair")
        std::cout << "fpair [sub-command] [names] --> performs action on header/source file pair\n"
                  << "  [sub-command] --> what operation to perform on file pair\n"
                  << "    create --> creates new file pair\n"
                  << "    remove --> destroys existing file pair\n"
                  << "  [names] --> name(s) of file pairs\n"
                  << "  --hpp --> use hpp header format (only useful for create action)\n\n"
                  << "Ex: cpm fpair create utils";
      else if (command == "class")
        std::cout << "class [names] --> creates class based header/source file pair\n"
                  << "  [names] --> what name(s) to use (class names will automatically be capitalized)\n"
                  << "    if file does not exist, a file pair will be created automatically\n\n"
                  << "Variations:\n"
                  << "  -p=[parent name] --> creates child class from parent class located in <parent name>.<h/hpp>\n"
                  << "    Default: class A: public B\n"
                  << "    --private --> class A: private B\n"
                  << "    --protected --> class A: protected B\n"
                  << "  --singleton --> creates singleton based file pairs\n\n"
                  << "Ex: cpm class engine axle tire headlight taillight";
      else if (command == "config")
      {
        std::cout << "config [sub-command] [key] {value} --> performs action on cpm config\n"
                  << "  [sub-command] --> what operation to perform on config\n"
                  << "    set [key] [value] --> add / edit key-value pair (requires value)\n"
                  << "    remove [key] --> removes key-value pair (doesn't require value)\n"
                  << "  [key] --> used to index config and search for value\n"
                  << "  {value} --> a value\n\n"
                  << "Logger Config Variables:\n"
                  << "  color_success\n  color_error\n  color_warn\n  color_theme\n  color_warn\n  color_count\n  color_prompt\n  color_execute\n\n"
                  << "Other Config Variables:\n"
                  << "  default_structure --> default project structure used in `cpm create`\n\n"
                  << "Ex: cpm config set colors_success blue";
      }
      else
      {
        logger.error_q("does not have any help-related information", command);
        return 1;
      }

      std::cout << "\n\n";
    }
    else
      std::cout << "Reading Guide (for more command specific information use <help (command)>):\n"
                << "  [Square brackets] are required arguments\n"
                << "  {Curly brackets} are optional arguments\n\n\n"
                << "Commands:\n"
                << "  help {command} --> lists commands + other useful information related to CPM\n"
                << "  version --> states version of CPM installed\n"
                << "  create [language] --> creates new c/c++ project\n"
                << "  fpair [sub-command] [names] --> performs action on header/source file pair\n"
                << "  class [names] --> creates class based header/source file pair\n"
                << "  config [sub-command] [key] {value} --> performs action on cpm config file\n"
                << "\n\n";

    std::cout << logger.colors["reset"];

    return 0;
  }

  /**
   * @brief Outputs current CPM version
   *
   * @return int
   */
  int version()
  {
    logger.custom("cpm version 0.1.0", "version", "red");

    return 0;
  }

  /**
   * @brief Creates new project in working directory
   *
   * @param args
   * @param flags
   * @return int
   */
  int create(const std::vector<std::string> &args, const std::vector<std::string> &flags)
  {
    // Language
    std::string lang = args[0];

    if (lang == "c++")
      lang = "cpp";

    if (lang != "cpp" & lang != "c")
    {
      logger.error_q("is not a supported language", lang);
      return 1;
    }

    const std::string project_name = logger.prompt("enter project name");

    // Structure
    const std::string default_structure = data_handler.config_has_key("default_structure") ? data_handler.config["default_structure"] : "executable";
    std::string structure;

    while (true)
    {
      structure = logger.prompt("enter project structure (hit enter for default '" + default_structure + "')");

      if (structure == "")
        structure = default_structure;

      if (!misc::vector_contains(supported_structures, structure))
        logger.warn_q("is an invald template name", structure);
      else
        break;
    }

    const bool git_support = logger.prompt_yn("add git support");

    std::string main_path;

    if (structure == "executable")
    {
      directory::create_folders({"src", "include", "build", "tests"});

      // Set main path to use src/
      main_path = "src/main";
      main_path += ((lang == "cpp") ? ".cpp" : ".c");

      // Get installed CMake version
      logger.execute("cmake --version > cpm.tmp");

      std::ifstream result_file("cpm.tmp");
      if (!misc::ifstream_open(result_file))
        return 1;

      std::string cmake_current_version;
      std::getline(result_file, cmake_current_version);
      cmake_current_version = misc::split_string(cmake_current_version, " ")[2];

      result_file.close();

      // Other CMake variables
      const std::string cmake_lang = (lang == "cpp") ? "CXX" : "C";
      const std::string lang_version = (flags.size() > 0) ? misc::get_flag_value(flags[0]) : "23";

      File cmake_lists("CMakeLists.txt");
      cmake_lists.load({
          "cmake_minimum_required(VERSION " + cmake_current_version + ")",
          "",
          "project(",
          "    " + project_name,
          "    LANGUAGES " + cmake_lang,
          ")",
          "",
          "set(CMAKE_" + cmake_lang + "_STANDARD " + lang_version + ")",
          "set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)",
          "",
          "file(GLOB SOURCES \"${SOURCE_DIR}/*.cpp\")",
          "",
          "add_executable(",
          "    ${PROJECT_NAME}",
          "    ${SOURCES}",
          ")",
          "",
          "target_include_directories(",
          "    ${PROJECT_NAME} PRIVATE",
          "    ${CMAKE_CURRENT_SOURCE_DIR}/include",
          ")",
          "",
          "target_link_libraries(",
          "    ${PROJECT_NAME} PRIVATE",
          ")",
          "",
          "if (CMAKE_SYSTEM_NAME MATCHES \"Darwin\" OR CMAKE_SYSTEM_NAME MATCHES \"Linux\")",
          "    install(TARGETS ${PROJECT_NAME} DESTINATION /usr/local/bin) # sudo required",
          "elseif (CMAKE_SYSTEM_NAME MATCHES \"Windows\")",
          "    install(TARGETS ${PROJECT_NAME} DESTINATION $ENV{ProgramFiles})",
          "endif()",
      });
    }
    else if (structure == "simple")
    {
      // Set main path to use ./
      main_path = "main";
      main_path += (lang == "cpp") ? ".cpp" : ".c";
    }

    if (git_support)
    {
      File gitignore(".gitignore");
      gitignore.load({
          "# CMake artifacts",
          "build",
          "CMakeFiles/",
          "CMakeCache.txt",
          "CMakeScripts/",
          "cmake_install.cmake",
          "Makefile",
          "",
          "# Testing",
          "tests",
          "",
          "# Others",
          ".exe",
          ".vscode/",
          ".DS_Store",
      });

      File readme("README.md");
      readme.load({"# " + project_name});

      directory::create_file("LICENSE");
    }

    File main_file(main_path);

    main_file.load({
        "#include <iostream>",
        "",
        "int main(int argc, char *argv[])",
        "{",
        "  std::cout << \"Hello World!\" << std::endl;",
        "  return 0;",
        "}",
    });

    return 0;
  }

  /**
   * @brief Creates / destroys header and source file pairs
   *
   * @param args
   * @param flags
   * @return int
   */
  int file_pair(const std::vector<std::string> &args, const std::vector<std::string> &flags)
  {
    // Whether to use include/ src/ folders
    for (const auto &arg : misc::sub_vector<std::string>(args, 1, args.size() - 1))
    {
      if (args[0] == "create")
      {
        const std::filesystem::path header_path(directory::get_structured_header_path(arg, (misc::vector_contains(flags, "hpp")))), source_path(directory::get_structured_source_path(arg));
        std::filesystem::path source_include_path;

        File header(header_path);
        header.load({"#pragma once"});

        if (source_path.parent_path() == header_path.parent_path())
          source_include_path = header_path.stem();
        else
          source_include_path = arg;

        File source(source_path);
        source.load({"#include \"" + source_include_path.string() + (misc::vector_contains(flags, "hpp") ? ".hpp" : ".h") + "\""});
      }
      else if (args[0] == "remove")
      {
        directory::destroy_file("include/" + arg + ".h");
        directory::destroy_file("include/" + arg + ".hpp");
        directory::destroy_file("src/" + arg + ".c");
        directory::destroy_file("src/" + arg + ".cpp");
        directory::destroy_file(arg + ".h");
        directory::destroy_file(arg + ".hpp");
        directory::destroy_file(arg + ".c");
        directory::destroy_file(arg + ".cpp");
      }
      else
      {
        logger.error_q("is an invalid sub-command", arg);
        return 1;
      }
    }

    return 0;
  }

  /**
   * @brief Inserts a coding template into file pair
   *
   * @param args
   * @param flags
   * @return int
   */
  int class_file_pair(const std::vector<std::string> &args, const std::vector<std::string> &flags)
  {
    if (directory::get_extension() == ".c")
    {
      logger.error("C programming language does not support classes");
      return 1;
    }

    // Create file pairs
    std::vector<std::string> file_pair_args = args;
    file_pair_args.insert(file_pair_args.begin(), "create");

    const int result = file_pair(file_pair_args, flags);

    if (result != 0)
      return result;

    // Open files
    std::string prefix_a, class_name;
    bool status = false;
    std::vector<std::string> split_arg;

    for (const auto &arg : args)
    {
      // Set '_arg' to filesystem::path from 'arg' so filename can be easily extracted
      std::filesystem::path _arg(arg);
      class_name = std::filesystem::absolute(_arg).filename().string();
      misc::auto_capitalize(class_name);

      // Write to files
      prefix_a = class_name + "::";

      // Write to files
      File header(directory::get_structured_header_path(arg, misc::vector_contains(flags, "hpp"))), source(directory::get_structured_source_path(arg));

      if (misc::vector_contains(flags, "singleton"))
      {
        header.write({
            "class " + class_name,
            "{",
            "private:",
            "  " + class_name + "();",
            "",
            "public:",
            "  " + class_name + "(const " + class_name + " &obj) = delete;",
            "",
            "  static " + class_name + " &get();",
            "};",
        });

        source.write({
            class_name + " &" + prefix_a + "get()",
            "{",
            "  static " + class_name + " obj;",
            "  return obj;",
            "}",
        });
      }
      else if (flags.size() > 0 && flags[0][0] == 'p') // inheritance
      {
        // Set '_arg' to path of parent header file
        _arg = misc::get_flag_value(flags[0]);
        const std::filesystem::path header_p_path(std::filesystem::absolute(directory::get_structured_header_path(_arg, !directory::has_file(directory::get_structured_header_path(_arg)))));

        if (!directory::has_file(header_p_path))
        {
          logger.error_q("does not exist", header_p_path);
          return 1;
        }

        File header_p(header_p_path);

        // Switch 'private' to 'protected' if 'protected' doesn't already exist within the file
        if (!status && !header_p.exists("protected"))
        {
          header_p.replace_first_with("private", "protected");
          status = true;
        }

        // Get parent class name
        prefix_a = _arg.filename().string();
        misc::auto_capitalize(prefix_a);

        // Get inherit mode (public, protected, private)
        std::string inherit_mode = "public ";

        if (misc::vector_contains(flags, "protected"))
          inherit_mode = "protected ";
        else if (misc::vector_contains(flags, "private"))
          inherit_mode = "private ";

        // Auto relative path detection
        std::string include_path = "";
        const char path_diff = header.compare(header_p);

        // Construct header path from given relative path
        if (path_diff < 0)
        {
          // Figure out last common path
          const std::vector<std::string> split_header_p_path(misc::split_string(std::filesystem::absolute(header_p_path).string(), "/")), split_header_path(misc::split_string(std::filesystem::absolute(header.get_path()).string(), "/"));
          size_t location = 0;

          for (; location < split_header_p_path.size(); location++)
          {
            if (split_header_p_path[location] != split_header_path[location])
              break;
          }

          // Add ../ for every path it takes to get from the header path to the last common path
          for (size_t i = 0; i < (split_header_path.size() - location - 1); i++)
            include_path += "../";

          // Add the trimmed header_p_path to include_path
          include_path += header_p.trim(header).parent_path().string();
        }
        else if (path_diff > 0)
          include_path += header_p.trim(header).parent_path().string() + "/";

        if (include_path[include_path.size() - 1] != '/')
          include_path += "/";

        if (include_path.length() > 0 && include_path[0] == '/')
          include_path = include_path.substr(1);
        else if (include_path.length() > 1 && (include_path[0] == '.' & include_path[1] == '/'))
          include_path = include_path.substr(2);

        include_path += header_p_path.filename().string();

        // Write to files
        header.write({
            "#include \"" + include_path + "\"",
            "",
            "class " + class_name + ": " + inherit_mode + prefix_a,
            "{",
            "private:",
            "",
            "public:",
            "  " + class_name + "();",
            "  ~" + class_name + "();",
            "};",
        });

        prefix_a = class_name + "::";

        source.write({
            prefix_a + class_name + "() {}",
            prefix_a + "~" + class_name + "() {}",
        });
      }
      else
      {
        header.write({
            "class " + class_name,
            "{",
            "private:",
            "",
            "public:",
            "  " + class_name + "();",
            "  ~" + class_name + "();",
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

  int config(const std::vector<std::string> &args, const std::vector<std::string> &flags)
  {
    if (args[0] == "set")
    {
      if (args.size() < 3)
      {
        logger.error_q("sub-command requires at least 3 arguments", "set");
        return 1;
      }

      data_handler.config[args[1]] = args[2];
      logger.success_q("set to '" + args[2] + "'", args[1]);
    }
    else if (args[0] == "remove")
    {
      data_handler.config.erase(args[1]);
      logger.success_q("removed from config", args[1]);
    }
    else
    {
      logger.error_q("sub-command is not valid", args[0]);
      return 1;
    }

    return 0;
  }
} // namespace commands