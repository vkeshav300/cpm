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

namespace commands
{
  // Logger
  Logger *logger = Logger::get();

  /**
   * @brief All templates supported by the create command.
   *
   */
  std::vector<std::string> supported_bases = {
      "default",
      "standard",
  };

  /**
   * @brief Lists all commands and provides useful information about CPM.
   *
   * @return int
   */
  int help()
  {
    std::cout << "\n"
              << logger->colors["blue"]
              << "      ___           ___         ___     \n"
              << "     /  /\\         /  /\\       /__/\\    \n"
              << "    /  /:/        /  /::\\     |  |::\\   \n"
              << "   /  /:/        /  /:/\\:\\    |  |:|:\\  \n"
              << "  /  /:/  ___   /  /:/~/:/  __|__|:|\\:\\ \n"
              << " /__/:/  /  /\\ /__/:/ /:/  /__/::::| \\:\n"
              << " \\  \\:\\ /  /:/ \\  \\:\\/:/   \\  \\:\\~~\\__\\/\n"
              << "  \\  \\:\\  /:/   \\  \\::/     \\  \\:\\      \n"
              << "   \\  \\:\\/:/     \\  \\:\\      \\  \\:\\     \n"
              << "    \\  \\::/       \\  \\:\\      \\  \\:\\    \n"
              << "     \\__\\/         \\__\\/       \\__\\/    \n\n\n"
              << logger->colors["reset"];

    logger->custom("https://github.com/vkeshav300/cpm\n\n\n", "github",
                   "red");

    logger->custom("cpm <command> <args + flags>\n", "usage", "blue");

    std::cout << "Reading Guide:\n"
              << "[Square brackets] are required arguments\n"
              << "{Curly brackets} are flags (not required)\n\n\n"
              << "help --> lists commands + other useful information related to CPM\n\n"
              << "version --> tells current version of cpm you are using\n\n"
              << "create [language] --> creates new c/c++ project\n\n";

    logger->custom("arguments must be in order, but flags can be placed anywhere.", "note", "yellow");

    return 0;
  }

  /**
   * @brief Outputs current CPM version.
   *
   * @return int
   */
  int version()
  {
    logger->custom("cpm version 0.1.0", "version", "red");

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
    return false;
  }

  /**
   * @brief Initializes cpm in a directory.
   *
   * @param args Command arguments.
   * @return int
   */
  int create(const std::vector<std::string> &args)
  {
    std::string lang = args[0];

    if (lang == "c++")
      lang = "cpp";

    if (lang != "cpp" && lang != "c")
    {
      logger->error_q("is not a supported language", lang);
      return 1;
    }

    std::string project_name = logger->prompt("enter project name");

    std::string base = "default";

    if (logger->prompt_yn("use custom template"))
    {
      while (true)
      {
        base = logger->prompt("enter the name of a template you would like to use");

        if (misc::vector_contains(supported_bases, base))
          break;
        else
          logger->warn_q("is an invald template name", base);
      }
    }

    bool git_support = logger->prompt_yn("add git support");

    std::vector<std::string> folders = {"src"};
    std::vector<std::string> files = {"src/" + project_name + "." + lang, "cpm.json"};

    if (git_support)
    {
      files.emplace_back(".gitignore");
      files.emplace_back("README.md");
      files.emplace_back("LICENSE");
    }

    for (const auto &folder : folders)
      directory::create_directory(folder);

    for (const auto &file : files)
      directory::create_file(file);

    return 0;
  }
} // namespace commands