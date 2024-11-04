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

/**
 * @brief Reads file into vector containing individual lines
 * 
 * @return std::vector<std::string> 
 */
std::vector<std::string> File::read()
{
    reader.open(path);

    if (!misc::ifstream_open(reader))
        return {};

    std::vector<std::string> lines;
    std::string line;

    while (std::getline(reader, line))
        lines.emplace_back(line);

    return lines;
}

/**
 * @brief Finds first instance of 'token_f' in file and replaces it with 'token_r'
 * 
 * @param token_f 
 * @param token_r 
 */
void File::replace_first_with(const std::string &token_f, const std::string &token_r)
{
    const std::filesystem::path tmp_path(path.string() + ".tmp");

    writer.open(tmp_path);
    reader.open(path);

    if (!misc::ifstream_open(reader) || !misc::ofstream_open(writer))
        return;
    
    std::string line;
    size_t pos;
    bool searching = true;

    while (std::getline(reader, line))
    {
        if (searching && (pos = line.find(token_f)) != std::string::npos) // Replcae first instance of token_f with token_r
        {
            line.replace(pos, token_f.length(), token_r);
            searching = false;
        }

        writer << line << "\n";
    }
    
    writer.close();
    reader.close();

    if (!std::filesystem::remove(path))
        return;
    
    std::filesystem::rename(tmp_path, path);
}

/**
 * @brief Returns whether there is an actual file at 'path'
 * 
 * @return true 
 * @return false 
 */
bool File::exists()
{
    return std::filesystem::exists(std::filesystem::absolute(path));
}

std::ofstream File::writer;
std::ifstream File::reader;