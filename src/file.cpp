/**
 * @file file.cpp
 * @brief Gives functionality to file.h
 * @version 0.1
 * @date 2024-11-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "file.h"
#include "misc.h"

/**
 * @brief Construct a new File:: File object
 * 
 * @param _path 
 */
File::File(const std::filesystem::path &_path) : path(_path)
{
    // Create file
    writer.open(path, std::ios::app);
    writer.close();
}

/**
 * @brief Destroy the File:: File object
 * 
 */
File::~File()
{
    writer.close();
    reader.close();
}

/**
 * @brief Adds lines to file
 * 
 * @param lines 
 */
void File::write(const std::vector<std::string> &lines)
{
    writer.open(path, std::ios::app);

    if (!misc::ofstream_open(writer))
        return;

    for (const auto &line : lines)
        writer << "\n"
               << line;
    
    writer.close();
}

/**
 * @brief Overwrites file with given lines
 * 
 * @param lines 
 */
void File::load(const std::vector<std::string> &lines)
{
    writer.open(path);

    if (!misc::ofstream_open(writer))
        return;
    
    for (const auto &line : lines)
        writer << line
               << "\n";

    writer.close();
}

/**
 * @brief Removes file from computer
 * 
 */
void File::remove()
{
    writer.close();
    reader.close();

    std::filesystem::remove(std::filesystem::absolute(path));
}

std::ofstream File::writer;
std::ifstream File::reader;