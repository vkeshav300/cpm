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
std::mutex File::writer_mtx, File::reader_mtx;

/**
 * @brief Construct a new File:: File object
 * 
 */
File::File() {}

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
    if (writer.is_open())
        return 1;
    
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
    if (reader.is_open())
        return 1;

    reader.open(path);

    return misc::ifstream_open(reader);
}

/**
 * @brief Adds lines to file
 * 
 * @param lines 
 */
void File::write(const std::vector<std::string> &lines)
{
    std::lock_guard<std::mutex> lock(writer_mtx);

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
    std::lock_guard<std::mutex> lock(writer_mtx);

    if (!wopen(false))
        return;
    
    for (const auto &line : lines)
        writer << line
               << "\n";
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