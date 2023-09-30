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

#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>

#include <curl/curl.h>

/**
 * @brief Initializes CPM in a directory, and creates all the files needed for a basic project.
 * 
 * @param language 
 * @return int 
 */
int commands::init(std::string language)
{
    // * All folders and files to be created
    std::vector<std::string> default_folders = {"assets", "src", "include", "build", "tests"};
    std::vector<std::string> default_files = {".gitignore", "CMakeLists.txt", "README.md", "LICENSE", ".cpm", "src/main.cpp"};

    // * Create files and folders
    for (auto &folder : default_folders)
        directory::createFolder("./", folder);

    for (auto &file : default_files)
        directory::createFile("./", file);

    // * Populates files with default code / text
    if (language == "c")
    {
        directory::createFile("./src/", "main.c");

        {
            std::ofstream file_main("./src/main.c");
            file_main << "#include <iostream>\n\nint main(int argc, char *argv[])\n{\n    std::cout << \"Hello World!\" << std::endl;\n\n    return 0;\n}";
            file_main.close();
        }
        {
            std::ofstream file_cmake("./CMakeLists.txt");
            file_cmake << "# Minimum required version of CMake (cmake --version)\ncmake_minimum_required(VERSION 3.27.0)\n\n# Project info\nproject(project_name VERSION 0.0)\n\n# Giving CMake file structure info\nset(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)\n\n# Get all the source files in the SOURCE_DIR\nfile(GLOB SOURCES "
                       << "${SOURCE_DIR}/*.c"
                       << ")\n\nadd_executable(project_name ${SOURCES})\n\ntarget_include_directories(project_name PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)";
            file_cmake.close();
        }
        {
            std::ofstream file_cpm("./.cpm");
            file_cpm << "language: c";
            file_cpm.close();
        }
    }

    else if (language == "cpp" || language == "c++")
    {
        directory::createFile("./src/", "main.cpp");

        {
            std::ofstream file_main("./src/main.cpp");
            file_main << "#include <iostream>\n\nint main(int argc, char *argv[])\n{\n    std::cout << \"Hello World!\" << std::endl;\n\n    return 0;\n}";
            file_main.close();
        }
        {
            std::ofstream file_cmake("./CMakeLists.txt");
            file_cmake << "# Minimum required version of CMake (cmake --version)\ncmake_minimum_required(VERSION 3.27.0)\n\n# Project info\nproject(project_name VERSION 0.0)\n\n# Giving CMake file structure info\nset(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)\n\n# Get all the source files in the SOURCE_DIR\nfile(GLOB SOURCES "
                       << "${SOURCE_DIR}/*.cpp"
                       << ")\n\nadd_executable(project_name ${SOURCES})\n\ntarget_include_directories(project_name PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)";
            file_cmake.close();
        }
        {
            std::ofstream file_cpm("./.cpm");
            file_cpm << "language: cpp";
            file_cpm.close();
        }
    }

    else
    {
        std::cerr << "\x1b[0;31m[error]: \x1b[0m"
                  << "\'"
                  << language
                  << "\' is an unsupported programming language\n";
    }

    {
        std::ofstream file_ignore("./.gitignore");
        file_ignore << "# CMake generated files and directories\n/build/build\nCMakeFiles/\nCMakeCache.txt\nCMakeScripts/\ncmake_install.cmake\nMakefile\n\n# Other\n.exe\n.vscode/";
        file_ignore.close();
    }

    std::cout << "\x1b[0;32m[success]: \x1b[0m"
              << "populated files\n";

    // * Provided information
    std::cout << "\x1b[0;33m[note]: \x1b[0m"
              << "to best utilize this project structure, it is recommended that you know how to use CMake.\n";
    std::cout << "\x1b[0;33m[note]: \x1b[0m"
              << "to edit the name of the project, go into the CMakeLists.txt and change all the placeholders that read \'project_name\'.\n";

    return 0;
}

/**
 * @brief Checks if cpm has been initialized in the directory by looking for a "cpm" file.
 * 
 * @return true 
 * @return false 
 */
bool commands::verify_init()
{
    // * Verifies init has been run
    if (directory::hasFile("./", ".cpm"))
        return true;

    return false;
}

/**
 * @brief Creates a populated header and source file in a project directory.
 * 
 * @param method 
 * @param pair_name 
 * @param language 
 * @param optionals 
 * @return int 
 */
int commands::file_pair(int method, std::string pair_name, std::string language, std::vector<std::string> optionals)
{
    int initialized = static_cast<int>(verify_init());

    directory::createFolder("./", "src");
    directory::createFolder("./", "include");

    std::string header_file_extention = ".h";
    for (auto &optional : optionals)
    {
        if (optional == "-hpp")
        {
            header_file_extention = ".hpp";
            break;
        }
    }

    if (method == CREATE)
    {
        // * Create header file
        directory::createFile("./include/", pair_name + header_file_extention);

        {
            std::ofstream file_header("./include/" + pair_name + header_file_extention);
            file_header << "#pragma once";
        }

        switch (initialized)
        {
        case 0:
        {
            // * Create files
            if (language == "c" || language == "cpp")
            {
                std::string file_extension = (language == "c") ? ".c" : ".cpp";
                directory::createFile("./src/", pair_name + file_extension);
                
                {
                    std::ofstream file_source("./src/" + pair_name + file_extension);
                    file_source << "#include \"" + pair_name + header_file_extention + "\"";
                }
            }
            else
            {
                std::cerr << "\x1b[0;31m[error]: \x1b[0m"
                          << "\'" 
                          << language 
                          << "\' is an unsupported programming language\n";

                return 2;
            }
            break;
        }

        case 1:
        {
            // * Open and read .cpm file
            std::string cpm_contents = directory::slurp("./", ".cpm");

            // * Check for "language:" line
            bool found_language = false;
            std::string file_extension;
            if (cpm_contents.find("language: c") != std::string::npos || cpm_contents.find("language: cpp") != std::string::npos)
            {
                found_language = true;
                file_extension = (cpm_contents.find("language: cpp") != std::string::npos) ? ".cpp" : ".c";
                directory::createFile("./src/", pair_name + file_extension);
            }

            if (!found_language)
            {
                std::cerr << "\x1b[0;31m[error]: \x1b[0m"
                          << ".cpm file does not contain a valid \'language\' value\n";

                return 1;
            }

            // * Writing '#pragma once' to header file and '#include <header_file>' to source file
            {
                std::ofstream file_source("./src/" + pair_name + file_extension);
                file_source << "#include \"" + pair_name + header_file_extention + "\"";
            }
            break;
        }

        default:
            std::cerr << "\x1b[0;31m[error]: \x1b[0m"
                      << "unknown error occured reading initialized status\n";

            return 3;
        }
    }
    else if (method == DELETE)
    {
        // * Delete files
        // ? Note that this code is confusing because there is no checking of file (or folder) existance. Go to "directory.h" for clarification.
        directory::deleteFile("./include/", pair_name + ".h");
        directory::deleteFile("./include/", pair_name + ".hpp");
        directory::deleteFile("./src/", pair_name + ".c");
        directory::deleteFile("./src/", pair_name + ".cpp");
    }
    else
    {
        std::cerr << "\x1b[0;31m[error]: \x1b[0m"
                  << "unknown error occured reading method status\n";

        return 4;
    }

    return 0;
}

/**
 * @brief Lists all commands and provides useful information about CPM.
 * 
 * @return int 
 */
int commands::help()
{
    // * CPM ASCII Art
    std::cout << " ██████ ██████  ███    ███\n"
              << "██      ██   ██ ████  ████\n"
              << "██      ██████  ██ ████ ██\n"
              << "██      ██      ██  ██  ██\n"
              << " ██████ ██      ██      ██\n"
              << "https://github.com/vkeshav300/cpm";

    // * Usage
    std::cout << "\x1b[0;34m[usage]: \x1b[0m"
              << "cpm <command> <args>\n";

    // * Commands
    std::cout << "help --> lists commands + other useful information related to CPM.\n"
              << "--version || version --> tells current version of cpm you are using."
              << "init <language> --> sets up a new C or C++ project.\n"
              << "pair new <name> <optional -hpp for .hpp header> --> creates header/source file pair.\n"
              << "pair remove <name> --> gets rid of header/source file pair.\n";

    return 0;
}

void commands::version()
{
    std::cout << "\x1b[0;32m[success]: \x1b[0m"
              << "cpm version 0.1.0\n";
}