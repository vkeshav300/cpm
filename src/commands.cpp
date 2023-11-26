/**
 * @file commands.cpp
 * @brief This file contains the functionality of all commands.
 * @version 0.1
 * @date 2023-09-29
 *
 * @copyright Copyright (c) 2023
 *
 */
// ? Project headers
#include "commands.h"
#include "directory.h"
#include "logger.h"
#include "misc.h"

// ? Standard library
#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>
#include <vector>

// ? Libraries
#include <curl/curl.h>

namespace commands
{
    /**
     * @brief Initializes CPM in a directory, and creates all the files needed for a basic project.
     *
     * @param language The primary language the project will be coded in.
     * @return int
     */
    int init(const std::string language)
    {
        // * All folders and files to be created
        std::vector<std::string> default_folders = {"assets", "src", "include", "build", "tests"};
        std::vector<std::string> default_files = {".gitignore", "CMakeLists.txt", "README.md", "LICENSE", ".cpm", "src/main." + language};

        // * Create files and folders
        for (auto &folder : default_folders)
            directory::create_folder("./", folder);

        for (auto &file : default_files)
            directory::create_file("./", file);

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
                        << ".exe\n"
                        << "\n# Doxygen generation artifacts\n"
                        << "docs/html\n"
                        << "docs/latex\n"
                        << "\n# Other\n"
                        << ".vscode/\n"
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
        logger::custom("to best utilize this project structure, it is recommended that you know how to use CMake.", "important", "yellow");
        logger::custom("make sure to edit all the placeholders in your \"CMakeLists.txt\" file.", "important", "yellow");

        return 0;
    }

    /**
     * @brief Initializes CPM in a pre-existing project.
     *
     * @param language The primary language the project is coded in.
     * @return int
     */
    int post_init(const std::string language)
    {
        directory::create_file("./", ".cpm");

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
        if (directory::has_file("./", ".cpm"))
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
    int file_pair(const std::vector<std::string> &arguments, const bool hpp, const std::string language)
    {
        if (arguments.size() < 1)
        {
            logger::error("minimum amount of arguments not met");
        }

        directory::create_folder("./", "src");
        directory::create_folder("./", "include");

        std::string sub_command = arguments[0];
        std::string header_file_extention = (hpp) ? ".hpp" : ".h";
        std::string src_file_extention = (language == "c") ? ".c" : ".cpp";
        const std::vector<std::string> pair_names = misc::sub_vector(arguments, 1, arguments.size());

        if (sub_command == "new")
        {
            for (auto &pair_name : pair_names)
            {
                // * Create header and source files, then populate them
                directory::create_file("./include/", pair_name + header_file_extention);

                {
                    std::ofstream file_header("./include/" + pair_name + header_file_extention);
                    file_header << "#pragma once";
                    file_header.close();
                }

                directory::create_file("./src/", pair_name + src_file_extention);
                {
                    std::ofstream file_main("./src/" + pair_name + src_file_extention);
                    file_main << "#include \"" + pair_name + header_file_extention + "\"";
                    file_main.close();
                }
            }
        }
        else if (sub_command == "remove")
        {
            for (auto &pair_name : pair_names)
            {
                // * Delete files
                directory::delete_file("./include/", pair_name + header_file_extention);
                directory::delete_file("./src/", pair_name + src_file_extention);
            }
        }
        else
        {
            // * Invalid "method" of dealing with files
            logger::error_q("is not a valid sub command", sub_command);

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
        logger::custom("cpm <command> <args> <opt (optional) flags>", "usage", "blue");

        // * Commands
        std::cout << "help --> lists commands + other useful information related to CPM.\n\n"
                  << "--version || version --> tells current version of cpm you are using.\n\n"
                  << "init <language> --> sets up a new C or C++ project.\n\n"
                  << "pair new <name> --> creates header/source file pair.\n\n"
                  << "pair new <name> -hpp --> creates header/source file pair (header file will be in .hpp format).\n\n"
                  << "pair remove <name> --> gets rid of header/source file pair.\n\n"
                  << "contents copy <copy from> <copy to> --> copies contents of one file to another (will erase all data from copy to file).\n\n"
                  << "contents copy -app/-append --> copies contents of one file to another (will not erase contents of copy to file).\n\n"
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
    int contents(const std::vector<std::string> &arguments, const std::vector<std::string> &flags)
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
            if (!directory::has_file("./", file_primary_s))
            {
                logger::error_q("does not exist", file_primary_s);
                return 1;
            }

            if (!directory::has_file("./", file_target_s))
                directory::create_file("./", file_target_s);

            // * Copying file
            std::ifstream file_primary;
            file_primary.open(file_primary_s);

            {
                std::ofstream file_target;

                if (misc::find_in_vector(flags, "-append") || misc::find_in_vector(flags, "-app"))
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

    /**
     * @brief CURL --> Calculates total size of received data and appends it to a string
     *
     * @param contents
     * @param size
     * @param nmemb
     * @param output
     * @return size_t
     */
    size_t write_callback(void *contents, size_t size, size_t nmemb, std::string *output)
    {
        size_t total_size = size * nmemb;
        output->append(static_cast<char *>(contents), total_size);
        return total_size;
    }

    /**
     * @brief Installs package from github link
     *
     * @param arguments
     * @param flags
     * @param language
     * @return int
     */
    int install(const std::vector<std::string> &arguments, const std::vector<std::string> &flags, const std::string language)
    {
        // * Assert proper amount of arguments
        if (arguments.size() < 1)
        {
            logger::error("invalid amount of arguments");
            return 1;
        }

        // * CURL setup
        std::string package_url = arguments[0];

        CURL *curl;
        CURLcode res;

        curl = curl_easy_init();

        // * Assert CURL
        if (!curl)
        {
            logger::error("failed to init curl");
            return 1;
        }

        curl_easy_setopt(curl, CURLOPT_URL, package_url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        // * Request timeout
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

        // * Configures response
        std::string response;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        res = curl_easy_perform(curl);

        // * Assert curl_easy_perform didn't fail
        if (res != CURLE_OK)
        {
            logger::error_q(": curl_easy_perform() failed", curl_easy_strerror(res));
            curl_easy_cleanup(curl);
            return 1;
        }

        // * Check response code
        long http_code = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

        if (http_code >= 200 && http_code < 300)
            logger::success("validated package url");
        else
        {
            logger::error("invalid package url");
            curl_easy_cleanup(curl);
            return 1;
        }

        // * CURL cleanup
        curl_easy_cleanup(curl);

        return 0;
    }

    /**
     * @brief Uninstalls package
     *
     * @param arguments
     * @return int
     */
    int uninstall(std::vector<std::string> &arguments)
    {
        return 0;
    }
}