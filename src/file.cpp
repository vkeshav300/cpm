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


std::ofstream File::writer;
std::ifstream File::reader;

/**
 * @brief Construct a new File:: File object
 * 
 * @param _path 
 */
File::File(const std::filesystem::path &_path) : path(_path)
{
    // Create file
    wopen(false);
    writer.close();
}

/**
 * @brief Opens file object with ofstream
 * 
 * @return int 
 */
int File::wopen(const bool &append)
{
    if (append)
        writer.open(path, std::ios::app);
    else
        writer.open(path);

    return misc::ofstream_open(writer);
}

/**
 * @brief Opens file object with ifstream
 * 
 * @return int 
 */
int File::ropen()
{
    reader.open(path);

    return misc::ifstream_open(reader);
}

/**
 * @brief Adds line to file
 * 
 * @param line 
 */
void File::write_line(const std::string &line)
{
    if (!wopen())
        return;
    
    writer << "\n"
           << line;
    
    writer.close();
}

/**
 * @brief Adds lines to file
 * 
 * @param lines 
 */
void File::write_lines(const std::vector<std::string> &lines)
{
    if (!wopen())
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
    if (!wopen(false))
        return;
    
    for (const auto &line : lines)
        writer << "\n"
               << line;
}