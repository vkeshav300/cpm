/**
 * @file commands.cpp
 * @brief Contains the functionality of all commands.
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

#include <fstream>
#include <cstdlib>
#include <iostream>

namespace commands
{
  // Logger
  Logger &logger = Logger::get();
  Data_Handler &data_handler = Data_Handler::get();

  /**
   * @brief All templates supported by the create command.
   *
   */
  std::vector<std::string> supported_structures = {
      "default",
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
  int test(const std::vector<std::string> &args, const std::vector<std::string> &flags)
  {
    return 0;
  }

  /**
   * @brief Lists all commands and provides useful information about CPM.
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

    logger.custom("https://github.com/vkeshav300/cpm\n\n\n", "github",
                  "red");

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
                  << "  default  --> 'executable' project structure, built around CMake\n"
                  << "  executable --> alias for 'default'\n"
                  << "  simple   --> only creates one main file in working directory\n\n"
                  << "Ex: cpm create cpp";
      else if (command == "fpair")
        std::cout << "fpair [sub-command] [names] --> performs action on header/source file pair\n"
                  << "  [sub-command] --> what operation to perform on file pair\n"
                  << "    create --> creates new file pair\n"
                  << "    remove --> destroys existing file pair\n"
                  << "  [names] --> name(s) of file pairs\n"
                  << "  -hpp --> use hpp header format (only useful for create action)\n\n"
                  << "Ex: cpm fpair create utils";
      else if (command == "class")
        std::cout << "class [names] --> creates class based header/source file pair\n"
                  << "  [names] --> what name(s) to use (class names will automatically be capitalized)\n"
                  << "    if file does not exist, a file pair will be created automatically\n\n"
                  << "Variations:\n"
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
   * @brief Outputs current CPM version.
   *
   * @return int
   */
  int version()
  {
    logger.custom("cpm version 0.1.0", "version", "red");

    return 0;
  }

  /**
   * @brief Checks if cpm has been initialized in the directory by looking for a
   * "cpm" file.
   *
   * @return true
   * @return false
   */
  bool verify_init()
  {
    return directory::has_file("cpm.data");
  }

  /**
   * @brief Creates new project in working directory.
   *
   * @param args
   * @param flags
   * @return int
   */
  int create(const std::vector<std::string> &args, const std::vector<std::string> &flags)
  {
    std::string lang = args[0];

    if (lang == "c++")
      lang = "cpp";

    if (lang != "cpp" && lang != "c")
    {
      logger.error_q("is not a supported language", lang);
      return 1;
    }

    std::string project_name = logger.prompt("enter project name");

    std::string structure;

    if (logger.prompt_yn("use custom template"))
    {
      while (true)
      {
        structure = logger.prompt("enter the name of a template you would like to use");

        if (!misc::vector_contains(supported_structures, structure))
          logger.warn_q("is an invald template name", structure);
        else
          break;
      }
    }
    else
      structure = "default";

    bool git_support = logger.prompt_yn("add git support");

    std::vector<std::string> folders = {};

    std::vector<std::string> files = {};

    std::string main_file;

    if (structure == "default" || structure == "executable")
    {
      folders.emplace_back("include");
      folders.emplace_back("build");
      folders.emplace_back("tests");
      folders.emplace_back("src");

      files.emplace_back("CMakeLists.txt");

      main_file = "src/" + project_name + "." + lang;
      files.emplace_back(main_file);
    }
    else if (structure == "simple")
    {
      main_file = project_name + "." + lang;
      files.emplace_back(main_file);
    }

    if (git_support)
    {
      files.emplace_back(".gitignore");
      files.emplace_back("LICENSE");
    }

    for (const auto &folder : folders)
      directory::create_directory(folder);

    for (const auto &file : files)
      directory::create_file(file);

    // Writing to files
    std::ofstream writing_file;
    std::ifstream reading_file;

    // <project-name>.c / <project-name>.cpp
    writing_file.open(main_file);

    if (!misc::ofstream_open(writing_file))
      return 1;

    /*
    #include <iostream>

    int main(int argc, char *argv[])
    {
      std::cout << "Helo World" << std::endl;
      return 0;
    }
    */
    writing_file << "#include <iostream>\n"
                 << "\n"
                 << "int main(int argc, char *argv[])\n"
                 << "{\n"
                 << "  std::cout << \"Hello World!\" << std::endl;"
                 << "  return 0;\n"
                 << "}";

    writing_file.close();

    // CMakeLists.txt
    if (misc::vector_contains(files, "CMakeLists.txt") && logger.execute("cmake --version"))
    {
      writing_file.open("CMakeLists.txt");
      reading_file.open("cpm.tmp");

      if (!misc::ofstream_open(writing_file) || !misc::ifstream_open(reading_file))
        return 1;

      // Use installed CMAKE version
      std::string cmake_current_version;
      std::getline(reading_file, cmake_current_version);
      cmake_current_version = misc::split_string(cmake_current_version, " ")[2];

      std::string cmake_lang = (lang == "cpp") ? "CXX" : "C";
      std::string version = (flags.size() > 0) ? misc::get_flag_value(flags[0]) : "23";

      /*
      cmake_minimum_required(VERSION <version>)

      project(
        <project name>
        LANGUAGES <C/CXX>
      )

      set(CMAKE_<C/CXX>_STANDARD <version>)
      */
      writing_file << "cmake_minimum_required(VERSION "
                   << cmake_current_version
                   << ")\n\n"
                   << "project(\n"
                   << "    "
                   << project_name
                   << "\n"
                   << "    LANGUAGES "
                   << cmake_lang
                   << "\n)\n\n"
                   << "set(CMAKE_"
                   << cmake_lang
                   << "_STANDARD "
                   << version
                   << ")\n";

      reading_file.close();
      writing_file.close();
    }

    if (misc::vector_contains(files, ".gitignore"))
    {
      writing_file.open(".gitignore");

      if (!misc::ofstream_open(writing_file))
        return 1;

      /*
      # CMake artifacts
      build
      CMakeFiles/
      CMakeCache.txt
      CMakeScripts/
      cmake_install.cmake
      Makefile

      # Doxygen artifacts
      docs/html
      docs/latex

      # Testing
      tests

      # Other
      .exe
      .vscode/
      README_tmp.html
      README.pdf
      .DS_Store
      */
      writing_file << "# CMake artifacts\n"
                   << "build\n"
                   << "CMakeFiles/\n"
                   << "CMakeCache.txt\n"
                   << "CMakeScripts/\n"
                   << "cmake_install.cmake\n"
                   << "Makefile\n\n"
                   << "# Doxygen artifacts\n"
                   << "docs/html\n"
                   << "docs/latex\n\n"
                   << "# Testing\n"
                   << "tests\n\n"
                   << "# Other\n"
                   << ".exe\n"
                   << ".vscode/\n"
                   << ".DS_Store";

      writing_file.close();
    }

    return 0;
  }

  /**
   * @brief Creates / destroys header and source file pairs.
   *
   * @param args
   * @param flags
   * @return int
   */
  int file_pair(const std::vector<std::string> &args, const std::vector<std::string> &flags)
  {
    // Whether to use include/ src/ folders
    bool prefix = (directory::get_structure() == "default") ? true : false;

    for (const auto &arg : misc::sub_vector<std::string>(args, 1, args.size() - 1))
    {
      if (args[0] == "create")
      {
        // File related variables
        std::string header_extension = (misc::vector_contains(flags, "hpp")) ? ".hpp" : ".h";
        std::string header_path = (prefix ? "include/" : "") + arg + header_extension;
        std::string source_path = (prefix ? "src/" : "") + arg + directory::get_extension();

        // Creating and writing to header file
        std::ofstream file(header_path);

        if (!misc::ofstream_open(file))
          return 1;

        file << "#pragma once";

        file.close();

        // Creating and writing to source file
        file.open(source_path);

        if (!misc::ofstream_open(file))
          return 1;

        /*
        #include <name>.<extension>
         */
        file << "#include \""
             << arg
             << header_extension
             << "\"";
      }
      else if (args[0] == "remove")
      {
        if (prefix)
        {
          directory::destroy_file("include/" + arg + ".h");
          directory::destroy_file("include/" + arg + ".hpp");
          directory::destroy_file("src/" + arg + ".c");
          directory::destroy_file("src/" + arg + ".cpp");
        }
        else
        {
          directory::destroy_file(arg + ".h");
          directory::destroy_file(arg + ".hpp");
          directory::destroy_file(arg + ".c");
          directory::destroy_file(arg + ".cpp");
        }
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
    // Create file pairs
    std::vector<std::string> file_pair_args = args;
    file_pair_args.insert(file_pair_args.begin(), "create");

    const int result = file_pair(file_pair_args, flags);

    if (result != 0)
      return result;

    // Open files
    std::ofstream header_file, source_file;

    bool prefix = (directory::get_structure() == "default") ? true : false;
    std::string prefix_a;

    for (const auto &arg : args)
    {
      header_file.open(
          (prefix ? "include/" : "") +
              arg +
              (misc::vector_contains(flags, "hpp") ? ".hpp" : ".h"),
          std::ios::app);

      source_file.open(
          (prefix ? "src/" : "") +
              arg +
              directory::get_extension(),
          std::ios::app);

      if (!misc::ofstream_open(header_file) || !misc::ofstream_open(source_file))
        return 1;

      header_file << "\n\n";
      source_file << "\n\n";

      // Automatic capitalization
      std::string letter(1, std::toupper(arg[0]));
      std::string class_name = letter + ((arg.length() > 1) ? arg.substr(1) : "");

      // TODO: Automatically capitalize letters after underscores or dashes

      // Writing files
      if (misc::vector_contains(flags, "singleton"))
      {
        /*
        class <Name>
        {
        private:
          <Name>();

        public:
          <Name>(const <Name> &obj) = delete;

          static <Name> &get();
        };
        */
        header_file << "class "
                    << class_name
                    << "\n{\n"
                    << "private:\n"
                    << "  "
                    << class_name
                    << "();\n\n"
                    << "public:\n"
                    << "  "
                    << class_name
                    << "("
                    << "const "
                    << class_name
                    << " &obj) = delete;\n\n"
                    << "  static "
                    << class_name
                    << " &get();\n"
                    << "};";

        /*
        <Name> &<Name>::get()
        {
          static <Name> obj;
          return obj;
        }
        */
        source_file << class_name
                    << " &"
                    << class_name
                    << "::get()\n"
                    << "{\n"
                    << "  static "
                    << class_name
                    << " obj;\n"
                    << "  return obj;\n"
                    << "}";
      }
      else // Default class code
      {
        /*
            class <name>
            {
            private:
            public:
              <name>();
              ~<name>();
            };
            */
        header_file << "class "
                    << class_name
                    << "\n{\n"
                    << "private:\n"
                    << "public:\n"
                    << "  "
                    << class_name
                    << "();\n\n"
                    << "  ~"
                    << class_name
                    << "();\n"
                    << "};";

        /*
        <name>::<name>() {}

        <name>::~<name>() {}
        */
        prefix_a = class_name + "::";
        source_file << prefix_a
                    << class_name
                    << "() {}\n\n"
                    << prefix_a
                    << "~"
                    << class_name
                    << "() {}";
      }

      header_file.close();
      source_file.close();
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