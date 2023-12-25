/**
 * @file directory.cpp
 * @brief This file contains most directory-related functions that aren't commands.
 * @version 0.1
 * @date 2023-09-29
 *
 * @copyright Copyright (c) 2023
 *
 */
// ? Project headers
#include "directory.h"
#include "logger.h"

// ? Standard library
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

namespace directory
{
    /**
     * @brief Reads file into string. WARNING: Should only be used for small files, as all contents will be loaded into one string.
     * @warning Should only be used for small files, as all contents will be loaded into one string.
     *
     * @param dir Directory file is located in.
     * @param filename Name of the file.
     * @return std::string
     */
    std::string slurp(std::string dir, std::string filename)
    {
        // * Checking if file exists
        if (!has_file(dir, filename))
        {
            logger::error("\'" + filename + "\' does not exist at \'" + dir + "\'");

            return NULL;
        }

        // * Opening the file
        std::string filepath = dir + filename;

        std::ifstream file;
        file.open(filepath);

        // * Reading contents of the file
        std::string contents;
        char ch;

        while (file.get(ch))
            contents += ch;

        file.close();

        return contents;
    }

    /**
     * @brief Checks if a file has specific contents.
     *
     * @param text Text to search in.
     * @param contents Contents to search for.
     * @return true
     * @return false
     */
    bool has_contents(std::string text, std::string contents)
    {
        return (text.find(contents) != std::string::npos);
    }

    /**
     * @brief Checks if directory has a file.
     *
     * @param dir Directory file is located in.
     * @param filename Name of the file.
     * @return true
     * @return false
     */
    bool has_file(std::string dir, std::string filename)
    {
        std::string filepath = dir + filename;

        return std::filesystem::exists(filepath) && std::filesystem::is_regular_file(filepath);
    }

    /**
     * @brief Checks if directory has a folder.
     *
     * @param dir Directory folder is located in.
     * @param foldername Name of the folder.
     * @return true
     * @return false
     */
    bool has_folder(std::string dir, std::string foldername)
    {
        std::string folderpath = dir + foldername;

        return std::filesystem::exists(folderpath) && std::filesystem::is_directory(folderpath);
    }

    /**
     * @brief Creates file in directory.
     *
     * @param dir Directory file will be located in.
     * @param filename Name of the file to be created.
     */
    void create_file(std::string dir, std::string filename)
    {
        std::string filepath = dir + filename;

        if (has_file(dir, filename))
            return;

        std::ofstream file(filepath);
        file.close();

        if (!has_file(dir, filename))
        {
            logger::error_q("could not be created", filepath);

            return;
        }

        logger::custom(filepath, "created", "magenta");
    }

    /**
     * @brief Creates folder in directory.
     *
     * @param dir Directory folder will be located in.
     * @param foldername Name of the folder to be created.
     */
    void create_folder(std::string dir, std::string foldername)
    {
        std::string folderpath = dir + foldername;

        if (has_folder(dir, foldername))
            return;

        std::filesystem::create_directory(folderpath);

        if (!has_folder(dir, foldername))
        {
            logger::error_q("could not be created", folderpath);

            return;
        }

        logger::custom(folderpath, "created", "magenta");
    }

    /**
     * @brief Deletes file in directory.
     *
     * @param dir Directory file is located in.
     * @param filename Name of the file.
     */
    void delete_file(std::string dir, std::string filename)
    {
        std::string filepath = dir + filename;

        if (!has_file(dir, filename))
            return;

        std::filesystem::remove(filepath);

        if (has_file(dir, filename))
        {
            logger::error_q("could not be deleted", filepath);
            return;
        }

        logger::custom(filepath, "deleted", "magenta");
    }
}