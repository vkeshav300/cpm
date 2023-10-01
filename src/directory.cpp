/**
 * @file directory.cpp
 * @brief This file contains most directory-related functions that aren't commands.
 * @version 0.1
 * @date 2023-09-29
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "directory.h"
#include "logger.h"

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

namespace directory
{
    /**
     * @brief Reads file into string.
     *
     * @param dir Directory file is located in.
     * @param filename Name of the file.
     * @return std::string
     */
    std::string slurp(std::string dir, std::string filename)
    {
        // * Checking if file exists
        if (!hasFile(dir, filename))
        {
            std::cerr << "\x1b[0;31m[error]: \x1b[0m\'"
                      << filename
                      << "\' does not exist at \'"
                      << dir
                      << "\'\n";

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
    bool hasContents(std::string text, std::string contents)
    {
        if (text.find(contents) != std::string::npos)
            return true;

        return false;
    }

    /**
     * @brief Checks if directory has a file.
     *
     * @param dir Directory file is located in.
     * @param filename Name of the file.
     * @return true
     * @return false
     */
    bool hasFile(std::string dir, std::string filename)
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
    bool hasFolder(std::string dir, std::string foldername)
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
    void createFile(std::string dir, std::string filename)
    {
        std::string filepath = dir + filename;

        if (hasFile(dir, filename))
            return;

        std::ofstream file(filepath);
        file.close();

        if (!hasFile(dir, filename))
        {
            logger::error("failed to create file " + filepath);

            return;
        }

        logger::success("created file " + filepath);
    }

    /**
     * @brief Creates folder in directory.
     *
     * @param dir Directory folder will be located in.
     * @param foldername Name of the folder to be created.
     */
    void createFolder(std::string dir, std::string foldername)
    {
        std::string folderpath = dir + foldername;

        if (hasFolder(dir, foldername))
            return;

        std::filesystem::create_directory(folderpath);

        if (!hasFolder(dir, foldername))
        {
            logger::error("failed to create folder " + folderpath);

            return;
        }

        logger::success("created folder " + folderpath);
    }

    /**
     * @brief Deletes file in directory.
     *
     * @param dir Directory file is located in.
     * @param filename Name of the file.
     */
    void deleteFile(std::string dir, std::string filename)
    {
        std::string filepath = dir + filename;

        if (!hasFile(dir, filename))
            return;

        std::filesystem::remove(filepath);

        if (hasFile(dir, filename))
        {
            logger::error("failed to delete file " + filepath);

            return;
        }
    }
}