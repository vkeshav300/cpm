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
  std::vector<std::string> supported_bases = {
      "default",
      "standard",
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
    logger.execute("ls -la");

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
              << logger.colors["blue"]
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
    if (args.size() > 0)
    {
      std::string command = args[0];

      if (command == "help")
        std::cout << "help {command} --> gets information related to CPM and it's commands\n"
                  << "  {command} --> specific command to focus information on\n\n";
      else if (command == "version")
        std::cout << "version --> states version of CPM installed\n\n";
      else if (command == "create")
        std::cout << "create [language] --> creates new c/c++ project\n"
                  << "  [language] --> language project will be based off of, C or C++\n\n"
                  << "Different Project Templates:\n"
                  << "  default  --> 'full' project structure, built around CMake\n"
                  << "  standard --> alias for 'default'\n"
                  << "  simple   --> only creates one main file in working directory\n\n";
      else
        logger.error_q("does not have any help-related information", command);
    }
    else
      std::cout << "Reading Guide:\n"
                << "  [Square brackets] are required arguments\n"
                << "  {Curly brackets} are optional arguments / flags\n\n\n"
                << "Commands:\n"
                << "  help {command}    --> lists commands + other useful information related to CPM\n"
                << "  version           --> states version of CPM installed\n"
                << "  create [language] --> creates new c/c++ project\n\n";

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
   * @brief Initializes cpm in a directory.
   *
   * @param args Command arguments.
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

    std::string base;

    if (logger.prompt_yn("use custom template"))
    {
      while (true)
      {
        base = logger.prompt("enter the name of a template you would like to use");

        if (!misc::vector_contains(supported_bases, base))
          logger.warn_q("is an invald template name", base);
        else
          break;
      }
    }
    else
      base = "default";

    bool git_support = logger.prompt_yn("add git support");

    std::vector<std::string> folders = {};

    std::vector<std::string> files = {};

    std::string main_file;

    if (base == "default" || base == "standard")
    {
      folders.emplace_back("include");
      folders.emplace_back("build");
      folders.emplace_back("tests");
      folders.emplace_back("src");

      files.emplace_back("CMakeLists.txt");

      main_file = "src/" + project_name + "." + lang;
      files.emplace_back(main_file);
    }
    else if (base == "simple")
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

    writing_file.open(main_file);

    writing_file << "#include <iostream>\n"
                 << "\n"
                 << "int main(int argc, char *argv[])\n"
                 << "{\n"
                 << "  std::cout << \"Hello World!\" << std::endl;"
                 << "  return 0;\n"
                 << "}";

    writing_file.close();

    if (misc::vector_contains(files, "CMakeLists.txt") && logger.execute("cmake --version"))
    {
      writing_file.open("CMakeLists.txt");
      reading_file.open("cpm.tmp");

      std::string cmake_current_version;
      std::getline(reading_file, cmake_current_version);
      cmake_current_version = misc::split_string(cmake_current_version, " ")[2];

      std::string prefix = (lang == "cpp") ? "CXX" : "C";
      std::string version = (flags.size() > 0) ? misc::get_flag_value(flags[0]) : "23";

      writing_file << "cmake_minimum_required(VERSION "
                   << cmake_current_version
                   << ")\n\n"
                   << "project(\n"
                   << "    "
                   << project_name
                   << "\n"
                   << "    LANGUAGES "
                   << ((lang == "cpp") ? "CXX" : "C")
                   << "\n)\n\n"
                   << "set(CMAKE_"
                   << prefix
                   << "_STANDARD "
                   << version
                   << ")\n";

      writing_file.close();
    }

    reading_file.close();

    data_handler.data["language"] = lang;

    return 0;
  }
} // namespace commands