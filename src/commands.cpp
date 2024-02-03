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
#include "misc.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>
#include <vector>
#include <cstdio>
#include <filesystem>
#include <memory>
#include <curl/curl.h>
#include <json/json.h>

namespace commands
{
    /**
     * @brief Initializes CPM in a directory, and creates all the files needed for a basic project.
     *
     * @param language Programming language.
     * @return int
     */
    int init(const std::string language, const std::vector<std::string> &flags)
    {
        std::vector<std::string> default_folders = {"src", "include", "build", "tests", "docs"};
        std::vector<std::string> default_files = {".gitignore", "CMakeLists.txt", "README.md", "LICENSE", ".cpm", "src/main." + language};
        std::vector<std::string> files_to_erase;

        if (false == logger::yn_prompt("initialize with git support"))
        {
            logger::success("initializing project without git support");

            files_to_erase.emplace_back(".gitignore");
            files_to_erase.emplace_back("README.md");
        }
        else
            logger::success("initializing project with git support");

        misc::erase_from_vector(default_files, files_to_erase);

        std::string project_name = logger::input("project name");

        for (const auto &folder : default_folders)
            directory::create_folder("./", folder);

        for (const auto &file : default_files)
            directory::create_file("./", file);

        {
            std::string addon = ("c" == language) ? "" : "XX";
            std::string version = misc::get_flag_defined(flags, "v=");

            if (version.empty())
                version = ("c" == language) ? "17" : "20";

            std::ofstream file_cmake("./CMakeLists.txt");
            file_cmake << "# Minimum required version of CMake (cmake --version)\n"
                       << "cmake_minimum_required(VERSION 3.27.6)\n"
                       << "\n# Project info\n"
                       << "project(\n"
                       << "    " << project_name << "\n"
                       << "    VERSION 0.1\n"
                       << "    LANGUAGES C" << addon << "\n"
                       << ")\n"
                       << "\nset(CMAKE_C" << addon << "_STANDARD " << version << ")\n"
                       << "set(CMAKE_C" << addon << "_EXTENSIONS OFF)\n"
                       << "\n# Giving CMake file structure info\n"
                       << "set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)\n"
                       << "\n# Get all the source files in the SOURCE_DIR\n"
                       << "file(GLOB SOURCES \"${SOURCE_DIR}/*." << language << "\")\n"
                       << "\nadd_executable(" << project_name << "\n"
                       << "    ${SOURCES}\n"
                       << ")\n"
                       << "\ntarget_include_directories(" << project_name << " PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)\n"
                       << "\n# Check if the current platform is macOS\n"
                       << "if (CMAKE_SYSTEM_NAME MATCHES \"Darwin\" OR CMAKE_SYSTEM_NAME MATCHES \"Linux\")\n"
                       << "    # Specify the installation directory for macOS (e.g., /usr/local/bin)\n"
                       << "    install(TARGETS " << project_name << " DESTINATION /usr/local/bin)\n"
                       << "elseif (CMAKE_SYSTEM_NAME MATCHES \"Windows\")\n"
                       << "    install(TARGETS " << project_name << " DESTINATION $ENV{ProgramFiles})\n"
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
        if (misc::find_in_vector(default_files, ".gitignore"))
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

        logger::custom("to best utilize this project structure, it is recommended that you know how to use CMake.", "important", "yellow");

        if ("PLACEHOLDER" == project_name)
            logger::custom("make sure to edit all the placeholders in your \"CMakeLists.txt\" file.", "important", "yellow");

        return 0;
    }

    /**
     * @brief Initializes CPM in a pre-existing project.
     *
     * @param language Programming language.
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
        return (directory::has_file("./", ".cpm")) ? true : false;
    }

    /**
     * @brief Creates header/source file pair.
     *
     * @param arguments Command arguments.
     * @param hpp Create .hpp header or .h header.
     * @param language Programming language.
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
        std::string src_file_extention = ("c" == language) ? ".c" : ".cpp";
        const std::vector<std::string> pair_names = misc::sub_vector(arguments, 1, arguments.size());

        if ("new" == sub_command)
        {
            for (auto &pair_name : pair_names)
            {
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
        else if ("remove" == sub_command)
        {
            for (auto &pair_name : pair_names)
            {
                directory::delete_file("./include/", pair_name + ".h");
                directory::delete_file("./include/", pair_name + ".hpp");
                directory::delete_file("./src/", pair_name + src_file_extention);
            }
        }
        else
        {
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
        std::cout << "\n"
                  << logger::colors["blue"]
                  << " ██████ ██████  ███    ███\n"
                  << "██      ██   ██ ████  ████\n"
                  << "██      ██████  ██ ████ ██\n"
                  << "██      ██      ██  ██  ██\n"
                  << " ██████ ██      ██      ██\n\n"
                  << logger::colors["reset"];

        logger::custom("https://github.com/vkeshav300/cpm\n\n\n", "source code", "red");

        logger::custom("cpm <command> <args> <flags>\n", "usage", "blue");

        std::cout << "help --> lists commands + other useful information related to CPM\n\n"
                  << "--version || version --> tells current version of cpm you are using\n\n"
                  << "init <language> --> sets up a new C or C++ project\n"
                  << "init flag : -post --> sets up CPM in a preexisting project\n"
                  << "init flag : -v=<version> --> specifies custom version of programming language to be used for compiling\n"
                  << "pair new <name> --> creates header/source file pair\n"
                  << "pair remove <name> --> gets rid of header/source file pair\n"
                  << "pair flag : -hpp --> (if applicable to the sub-command), command will use .hpp files instead of .h files\n\n"
                  << "contents copy <copy from> <copy to> --> copies contents of one file to another (will erase all data from copy to file)\n"
                  << "contents erase <file> --> erases all contents from a file\n"
                  << "contents switch <file 1> <file 2> --> switches the contents of the two files\n"
                  << "contents flag : -app/-append --> (if applicable to the sub-command), will use append mode\n\n"
                  << "install <repository> --> <STILL BEING PROGRAMMED>\n"
                  << "uninstall <package_name> --> <STILL BEING PROGRAMMED>\n\n";

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
     * @param arguments Command arguments.
     * @param flags Command flags.
     * @return int
     */
    int contents(const std::vector<std::string> &arguments, const std::vector<std::string> &flags)
    {
        std::string sub_command = arguments[0];
        std::size_t arguments_amt = arguments.size();

        if (arguments_amt < 2)
        {
            logger::error("minimum amount of arguments not met");
            return 1;
        }

        if ("copy" == sub_command)
        {
            if (arguments_amt < 3)
            {
                logger::error("minimum amount of arguments not met");
                return 1;
            }

            std::string file_primary_s = arguments[1];
            std::string file_target_s = arguments[2];

            if (!directory::has_file("./", file_primary_s))
            {
                logger::error_q("does not exist", file_primary_s);
                return 1;
            }

            if (!directory::has_file("./", file_target_s))
            {
                logger::error_q("does not exist", file_target_s);
                return 1;
            }

            if (!directory::has_file("./", file_target_s))
                directory::create_file("./", file_target_s);

            std::ifstream file_primary;
            file_primary.open(file_primary_s);

            {
                std::ofstream file_target;

                if (misc::find_in_vector(flags, "append") || misc::find_in_vector(flags, "app"))
                    file_target.open(file_target_s, std::ios::app);
                else
                    file_target.open(file_target_s);

                char ch;

                while (file_primary.get(ch))
                    file_target << ch;

                file_target.close();
            }

            file_primary.close();

            logger::success((misc::find_in_vector(flags, "append") || misc::find_in_vector(flags, "app")) ? "copied " + file_primary_s + " to " + file_target_s + " with append mode" : "copied " + file_primary_s + " to " + file_target_s + " without append mode");
        }
        else if ("erase" == sub_command)
        {
            for (int i = 1; i < arguments.size(); i++)
            {
                std::string file_s = arguments[i];
                if (!directory::has_file("./", file_s))
                {
                    logger::error_q("does not exist", file_s);
                    continue;
                }

                std::ofstream file;
                file.open(file_s, std::ofstream::out | std::ofstream::trunc);
                file.close();

                logger::custom(file_s, "erased", "magenta");
            }
        }
        else if ("switch" == sub_command)
        {
            if (arguments_amt < 3)
            {
                logger::error("minimum amount of arguments not met");
                return 1;
            }

            std::string file_primary_s = arguments[1];
            std::string file_target_s = arguments[2];

            if (!directory::has_file("./", file_primary_s))
            {
                logger::error_q("does not exist", file_primary_s);
                return 1;
            }

            if (!directory::has_file("./", file_target_s))
            {
                logger::error_q("does not exist", file_target_s);
                return 1;
            }

            if (!directory::has_file("./", file_target_s))
            {
                logger::error_q("does not exist", file_target_s);
                return 1;
            }

            std::ifstream ifs_primary, ifs_target;
            std::ofstream ofs_primary, ofs_target;

            ifs_primary.open(file_primary_s);
            ifs_target.open(file_target_s);

            ofs_primary.open(file_primary_s + ".tmp");
            ofs_target.open(file_target_s + ".tmp");

            char ch;

            while (ifs_primary.get(ch))
                ofs_target.put(ch);

            while (ifs_target.get(ch))
                ofs_primary.put(ch);

            ifs_primary.close();
            ifs_target.close();
            ofs_primary.close();
            ofs_target.close();

            std::filesystem::remove(file_primary_s.c_str());
            std::filesystem::remove(file_target_s.c_str());

            if (directory::has_file("./", file_primary_s))
                logger::error_q("could not be deleted", file_primary_s);

            if (directory::has_file("./", file_target_s))
                logger::error_q("could not be deleted", file_target_s);

            std::filesystem::rename((file_primary_s + ".tmp").c_str(), file_primary_s.c_str());
            std::filesystem::rename((file_target_s + ".tmp").c_str(), file_target_s.c_str());

            logger::success("switched contents of " + file_primary_s + " and " + file_target_s);
        }
        else
        {
            logger::error_q("is an invalid sub-command", sub_command);
            return 1;
        }

        return 0;
    }

    /**
     * @brief Installs package from provided git repository.
     *
     * @param arguments Command arguments.
     * @param flags Command flags.
     * @param language Programming language.
     * @return int
     */
    int install(const std::vector<std::string> &arguments, const std::vector<std::string> &flags, const std::string language)
    {
        if (arguments.size() < 1)
        {
            logger::error("minimum amount of arguments not met");
            return 1;
        }

        std::string target_url = "https://github.com/" + arguments[0] + "/releases/latest";

        std::unique_ptr<CURL, decltype(&curl_easy_cleanup)> curl(curl_easy_init(), &curl_easy_cleanup);
        CURLcode res;

        if (!curl || !curl.get())
        {
            logger::error("failed to init CURL");
            return 1;
        }

        logger::success("initialized CURL");

        curl_easy_setopt(curl.get(), CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl.get(), CURLOPT_TIMEOUT, 5L);

        if (misc::curl_perform(curl, target_url))
            return 1;

        logger::success("setup CURL");

        if (misc::validate_url(curl, target_url))
            return 1;

        std::unique_ptr<char[]> final_url(nullptr);
        curl_easy_getinfo(curl.get(), CURLINFO_EFFECTIVE_URL, &final_url);

        if (!final_url.get())
        {
            logger::error("failed to retrieve final url");
            return 1;
        }

        target_url = std::string(final_url.get()) + "/cpm-install.zip";

        if (misc::curl_perform(curl, target_url))
            return 1;

        if (misc::validate_url(curl, target_url))
            return 1;

        target_url = "https://api.github.com/repos/" + arguments[0] + "/releases";

        std::string response;
        curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, misc::write_callback);
        curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, &response);

        if (misc::curl_perform(curl, target_url))
            return 1;

        Json::CharReaderBuilder json_reader;
        Json::Value release_info;
        std::istringstream json_stream(response);
        std::string errs;

        if (!Json::parseFromStream(json_reader, json_stream, &release_info, &errs))
        {
            std::cout << response << "\n";
            std::cout << release_info.toStyledString() << "\n"; // ! prints null -- no data read?
            misc::replace(errs, "\n", " : ");
            logger::error_q("failed to parse", errs);
            return 1;
        }

        curl_easy_setopt(curl.get(), CURLOPT_URL, release_info[0]["assets"][0]["browser_download_url"].asString().c_str());

        std::ofstream output_file("cpm_install.tmp.zip", std::ios::binary);
        curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, misc::write_file_callback);
        curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, &output_file);

        // TODO https://api.github.com/repos/{argument[0]}/releases -- validate api and download data from API

        res = curl_easy_perform(curl.get());
        output_file.close();

        if (res != CURLE_OK)
        {
            logger::error_q(": curl_easy_perform() : asset download failed", curl_easy_strerror(res));
            logger::custom("try seeing if the latest release on the repository contains a 'cpm_install.zip' file", "hint", "yellow");
            return 1;
        }

        logger::success("located installation files");

        if (!directory::has_file("./", "cpm_install.tmp.zip"))
        {
            logger::error("unable to download installation files");
            return 1;
        }

        logger::success("downloaded installation files");

        return 0;
    }

    /**
     * @brief Uninstalls package
     *
     * @param arguments Command arguments.
     * @return int
     */
    int uninstall(const std::vector<std::string> &arguments)
    {
        return 0;
    }
}
