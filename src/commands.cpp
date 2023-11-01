/**
 * @file commands.cpp
 * @brief This file contains the functionality of all commands.
 * @version 0.1
 * @date 2023-09-29
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "commands.h"
#include "directory.h"
#include "logger.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>
#include <vector>

namespace commands
{
    /**
     * @brief Initializes CPM in a directory, and creates all the files needed for a basic project.
     *
     * @param language The primary language the project will be coded in.
     * @return int
     */
    int init(std::string language)
    {
        // * All folders and files to be created
        std::vector<std::string> default_folders = {"assets", "src", "include", "build", "tests"};
        std::vector<std::string> default_files = {".gitignore", "CMakeLists.txt", "README.md", "LICENSE", ".cpm", "src/main." + language};

        // * Create files and folders
        for (auto &folder : default_folders)
            directory::createFolder("./", folder);

        for (auto &file : default_files)
            directory::createFile("./", file);

        // * Populates files with default code / text

        {
            // * Language-specific variables
            std::string addon = (language == "c") ? "" : "XX";
            std::string version = (language == "c") ? "20" : "21";

            std::ofstream file_cmake("./CMakeLists.txt");
            file_cmake << "# Minimum required version of CMake (cmake --version)"
                       << "cmake_minimum_required(VERSION 3.27.6)\n"
                       << "\n# Project info\n"
                       << "project(\n"
                       << "    PROJECT_NAME_HERE \n"
                       << "    VERSION 0.1\n"
                       << "    LANGUAGES C" << addon << "\n"
                       << ")\n"
                       << "\nset(CMAKE_C" << addon << "_STANDARD " << version << ")\n"
                       << "set(CMAKE_C" << addon << "_EXTENSIONS OFF)\n"
                       << "\n# Giving CMake file structure info\n"
                       << "set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)\n"
                       << "\n# Get all the source files in the SOURCE_DIR\n"
                       << "file(GLOB SOURCES \"${SOURCE_DIR}/*." << language << "\")\n"
                       << "\nadd_executable(EXECUTABLE_NAME_HERE\n"
                       << "    ${SOURCES}\n"
                       << ")\n"
                       << "\ntarget_include_directories(EXECUTABLE_NAME_HERE PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)\n"
                       << "\n# Check if the current platform is macOS\nif (CMAKE_SYSTEM_NAME MATCHES \"Darwin\")\n"
                       << "    # Specify the installation directory for macOS (e.g., /usr/local/bin)\n"
                       << "    install(TARGETS EXECUTABLE_NAME_HERE DESTINATION /usr/local/bin)\n"
                       << "endif()";
            file_cmake.close();
        }

        {
            std::ofstream file_main("./src/main." + language);
            file_main << "#include <iostream>\n"
                      << "\nint main(int argc, char *argv[])\n"
                      << "{\n    std::cout << \"Hello World\" << std::endl;\n"
                      << "\n    return 0;"
                      << "\n}";
            file_main.close();
        }
        {
            std::ofstream file_ignore("./.gitignore");
            file_ignore << "# CMake related files and directories\n"
                        << "/build/*\n"
                        << "/tests/*\n"
                        << "CMakeFiles/\n"
                        << "CMakeCache.txt\n"
                        << "CMakeScripts/\n"
                        << "cmake_install.cmake\n"
                        << "Makefile\n"
                        << "\n# Doxygen generation artifacts\n"
                        << "docs/html\n"
                        << "docs/latex\n"
                        << "\n# Other\n"
                        << ".exe\n"
                        << ".vscode/\n"
                        << "README_tmp.html\n"
                        << ".DS_Store";
            file_ignore.close();
        }
        {
            std::ofstream file_cpm("./.cpm");
            file_cpm << "language: "
                     << language;
            file_cpm.close();
        }

        logger::success("populated files");

        // * Provided information
        logger::custom("to best utilize this project structure, it is recommended that you know how to use CMake.", "note", "yellow");
        logger::custom("to edit the name of the project, go into the CMakeLists.txt and change all the placeholders that read \'project_name\'.", "note", "yellow");

        return 0;
    }

    /**
     * @brief Initializes CPM in a pre-existing project.
     *
     * @param language The primary language the project is coded in.
     * @return int
     */
    int post_init(std::string language)
    {
        directory::createFile("./", ".cpm");

        std::ofstream file_cpm("./.cpm");
        file_cpm << "language: "
                 << language;
        file_cpm.close();

        return 0;
    }

    /**
     * @brief Checks if cpm has been initialized in the directory by looking for a "cpm" file.
     *
     * @return true
     * @return false
     */
    bool verify_init()
    {
        // * Verifies init has been run
        if (directory::hasFile("./", ".cpm"))
            return true;

        return false;
    }

    /**
     * @brief Creates header/source file pair.
     *
     * @param arguments
     * @param hpp
     * @param language
     * @return int
     */
    int file_pair(std::vector<std::string> arguments, bool hpp, std::string language)
    {
        directory::createFolder("./", "src");
        directory::createFolder("./", "include");

        std::string header_file_extention = (hpp) ? ".hpp" : ".h";
        std::string pair_name = arguments[1];

        if (arguments[0] == "new")
        {
            // * Create header and source files, then populate them
            directory::createFile("./include/", pair_name + header_file_extention);

            {
                std::ofstream file_header("./include/" + pair_name + header_file_extention);
                file_header << "#pragma once";
                file_header.close();
            }

            {
                std::string file_extention = (language == "c") ? ".c" : ".cpp";

                std::ofstream file_main("./src/" + pair_name + file_extention);
                file_main << "#include \"" + pair_name + header_file_extention + "\"";
                file_main.close();
            }
        }
        else if (arguments[0] == "remove")
        {
            // * Delete files
            directory::deleteFile("./include/", pair_name + ".h");
            directory::deleteFile("./include/", pair_name + ".hpp");
            directory::deleteFile("./src/", pair_name + ".c");
            directory::deleteFile("./src/", pair_name + ".cpp");
        }
        else
        {
            // * Invalid "method" of dealing with files
            logger::error(arguments[0] + " is not a valid argument");

            return 1;
        }

        return 0;
    }

    /**
     * @brief Lists all commands and provides useful information about CPM.
     *
     * @return int
     */
    int help()
    {
        // * CPM ASCII Art
        std::cout << "\n"
                  << " ██████ ██████  ███    ███\n"
                  << "██      ██   ██ ████  ████\n"
                  << "██      ██████  ██ ████ ██\n"
                  << "██      ██      ██  ██  ██\n"
                  << " ██████ ██      ██      ██\n\n";

        logger::custom("https://github.com/vkeshav300/cpm\n", "source code", "red");

        // * Usage
        logger::custom("cpm <command> <args>", "usage", "blue");

        // * Commands
        std::cout << "help --> lists commands + other useful information related to CPM.\n\n"
                  << "--version || version --> tells current version of cpm you are using.\n\n"
                  << "init <language> --> sets up a new C or C++ project.\n\n"
                  << "pair new <name> <optional -hpp for .hpp header> --> creates header/source file pair.\n\n"
                  << "pair remove <name> --> gets rid of header/source file pair.\n\n"
                  << "contents copy <copy from> <copy to> <option -app/-append to append to file> --> copies contents of one file to another.\n\n"
                  << "contents erase <file> --> erases all contents from a file.\n\n";

        // * Other
        logger::custom("arguments must be in order, but flags can be placed anywhere after the command.", "note", "yellow");

        return 0;
    }

    /**
     * @brief Outputs current CPM version.
     *
     * @return int
     */
    int version()
    {
        logger::custom("cpm version 0.1.0", "version", "red");

        return 0;
    }

    /**
     * @brief Uses contents of files to execute sub-commands.
     *
     * @param arguments
     * @return int
     */
    int contents(std::vector<std::string> arguments, std::vector<std::string> flags)
    {
        std::string sub_command = arguments[0];
        int arguments_amt = arguments.size();

        // * Min amt of arguments (for entire command)
        if (arguments_amt < 2)
        {
            logger::error("minimum amount of arguments not met");
            return 1;
        }

        std::string file_primary_s = arguments[1];

        if (sub_command == "copy")
        {
            // * Min amt of arguments (for sub command)
            if (arguments_amt < 3)
            {
                logger::error("minimum amount of arguments not met");
                return 1;
            }

            // * The file to write to
            std::string file_target_s = arguments[2];

            // * Checking if files exist
            if (!directory::hasFile("./", file_primary_s))
            {
                logger::error_q("does not exist", file_primary_s);
                return 1;
            }

            if (!directory::hasFile("./", file_target_s))
                directory::createFile("./", file_target_s);

            // * Copying file
            std::ifstream file_primary;
            file_primary.open(file_primary_s);

            {
                std::ofstream file_target;

                if (std::find(flags.begin(), flags.end(), "-append") != flags.end() || std::find(flags.begin(), flags.end(), "-app") != flags.end())
                    file_target.open(file_target_s, std::ios::app);
                else
                    file_target.open(file_target_s);

                // * Reading / Writing
                char ch;

                while (file_primary.get(ch))
                    file_target << ch;

                file_target.close();
            }

            // * Closing files
            file_primary.close();
        }
        else if (sub_command == "erase")
        {
            std::ofstream file_primary;
            file_primary.open(file_primary_s, std::ofstream::out | std::ofstream::trunc);
            file_primary.close();
        }
        else
        {
            logger::error_q("is an invalid sub-command", sub_command);
            return 1;
        }

        return 0;
    }

    int insert(std::vector<std::string> arguments)
    {
        std::string template_type = arguments[0];
        std::string name = arguments[1];
        std::string filepath = arguments[2];

        if (!directory::hasFile("./", filepath))
        {
            logger::error_q("does not exist", filepath);
            return 1;
        }

        // * Opening file
        std::ofstream file_primary;
        file_primary.open(filepath, std::ios::app);

        // * Spacing
        file_primary << "\n\n";

        if (template_type == "class")
            file_primary << "class " << name << "\n"
                         << "{\n"
                         << "   private:\n"
                         << "\n"
                         << "   public:\n"
                         << "       " << name << "();"
                         << "       ~" << name << "();"
                         << "};";
        else if (template_type == "struct")
            file_primary << "struct " << name << "\n"
                         << "{\n"
                         << "   int id;\n"
                         << "   std::string name;\n"
                         << "   float value;\n"
                         << "};";
        else
        {
            logger::error_q("is not a valid template", template_type);
            return 1;
        }

        file_primary.close();

        return 0;
    }
}