/**
 * @file init_command.cpp
 * @brief Adds functionality to init command
 * @version 0.1
 * @date 2025-02-23
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "commands/init_command.h"

#include "config.h"
#include "directory.h"
#include "file.h"
#include "misc.h"

#include <fstream>

/**
 * @brief Construct a new Init_Command object
 *
 */
Init_Command::Init_Command() {}

/**
 * @brief Execute init command
 *
 * @param args
 * @param flags
 * @return uint8_t
 */
uint8_t Init_Command::execute(const std::vector<std::string> &args,
                              const std::vector<std::string> &flags) const {
  /* Language parsing */
  std::string lang = args[0];

  if (lang == "c++")
    lang = "cpp";

  if (lang != "cpp" & lang != "c") {
    logger.error_q("is not a supported language", lang);
    return 1;
  }

  /* Prompt project name */
  const std::string project_name = logger.prompt("enter project name");

  /* Directory structure */
  const std::string default_structure =
      data_manager.config_has_key("default_structure")
          ? data_manager.config["default_structure"]
          : "executable";
  std::string structure;

  /* Prompt structure */
  while (true) {
    structure =
        logger.prompt("enter project structure (hit enter for default '" +
                      default_structure + "')");

    if (structure == "")
      structure = default_structure;

    if (!misc::vector_contains(supported_structures, structure))
      logger.warn_q("is an invald template name", structure);
    else
      break;
  }

  const bool git_support = logger.prompt_yn("add git support");

  /* Set main path */
  std::string main_path;

  if (structure == "executable") {
    directory::create_folders({"src", "include", "build", "tests", "lib"});

    main_path = "src/main";
    main_path += ((lang == "cpp") ? ".cpp" : ".c");

    /* Get installed CMake version */
    logger.execute("cmake --version > cpm.tmp");

    std::ifstream result_file("cpm.tmp");
    if (!misc::ifstream_open(result_file))
      return 1;

    std::string cmake_current_version;
    std::getline(result_file, cmake_current_version);
    cmake_current_version = misc::split_string(cmake_current_version, " ")[2];

    result_file.close();

    /* Setup CMake variables / file */
    const std::string cmake_lang = (lang == "cpp") ? "CXX" : "C";
    const std::string lang_version =
        (flags.size() > 0)
            ? misc::get_flag_value(flags[0])
            : ((lang == "cpp") ? cpp_default_standard : c_default_standard);

    File cmake_lists("CMakeLists.txt");
    cmake_lists.load({
        "cmake_minimum_required(VERSION " + cmake_current_version + ")",
        "",
        "project(",
        "\t" + project_name,
        "\tLANGUAGES " + cmake_lang,
        ")",
        "",
        "set(CMAKE_" + cmake_lang + "_STANDARD " + lang_version + ")",
        "set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)",
        "",
        "file(GLOB_RECURSE SOURCES \"${SOURCE_DIR}/*." +
            std::string((lang == "cpp") ? "cpp" : "c") + "\")",
        "",
        "add_executable(",
        "\t${PROJECT_NAME}",
        "\t${SOURCES}",
        ")",
        "",
        "target_include_directories(",
        "\t${PROJECT_NAME} PRIVATE",
        "\t${CMAKE_CURRENT_SOURCE_DIR}/include",
        ")",
        "",
        "target_link_libraries(",
        "\t${PROJECT_NAME} PRIVATE",
        ")",
        "",
        "install(TARGETS ${PROJECT_NAME} DESTINATION /usr/local/bin)",
    });
  } else if (structure == "simple") {
    main_path = "main";
    main_path += (lang == "cpp") ? ".cpp" : ".c";
  }

  if (git_support) {
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
      "int main(int argc, char *argv[]) {",
      "\tstd::cout << \"Hello World!\" << std::endl;",
      "\treturn 0;",
      "}",
  });

  return 0;
}

std::string Init_Command::get_description() const {
  return "Initializes a new c/cpp project in working directory";
}

std::string Init_Command::get_arguments() const {
  return "[language] language project is based in";
}

std::string Init_Command::get_flags() const {
  return "-s=[language standard] specify a specific language standard to use "
         "instead of C" +
         std::string(c_default_standard) + " or C++" +
         std::string(cpp_default_standard);
}

uint16_t Init_Command::get_min_args() const { return 1; }