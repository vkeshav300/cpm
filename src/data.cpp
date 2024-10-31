/**
 * @file data.cpp
 * @brief Provides majority of functionality to Dat_Handler singleton.
 * @version 0.1
 * @date 2024-09-15
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "data.h"
#include "misc.h"
#include "directory.h"

#include <fstream>
#include <cstdlib>

#ifdef _WIN32

std::string get_store_location()
{
    return "";
}

#else

std::string get_store_location()
{
    // /Users/<user>/.config/cpm
    std::string home_loc = std::getenv("HOME");
    return  home_loc + "/.config/cpm";
}

#endif

/**
 * @brief Get method for DATA_HANDLER singleton class.
 *
 * @return Data_Handler&
 */
Data_Handler &Data_Handler::get()
{
    static Data_Handler obj;
    return obj;
}

/**
 * @brief Reads cpm.data file and stores it in data.
 *
 */
void Data_Handler::read()
{
    if (!directory::has_file("cpm.data"))
        return;

    std::ifstream data_file("cpm.data");

    if (!misc::ifstream_open(data_file))
        return;

    // Reading variables
    char ch, prevCh;
    std::string key, value;
    bool onKey = true;

    // Format --> key: value --> (key:<space>value\n)
    while (data_file.get(ch))
    {
        if (ch == '\n') // \n = newline = new key: value
        {
            data[key] = value;
            key = value = "";
            onKey = true;

            prevCh = ch;
            continue;
        }
        else if (prevCh == ':') // : = switch from key to value
        {
            prevCh = ch;
            continue;
        }
        else if (ch == ':') // space between colon and value
        {
            onKey = false;
            prevCh = ch;
            continue;
        }

        if (onKey)
        {
            key += ch;
            prevCh = ch;
            continue;
        }

        value += ch;
        prevCh = ch;
        continue;
    }

    data[key] = value;

    data_file.close();

    std::string config_location = get_store_location();

    if (!directory::has_directory(config_location))
        return;

    config_location += "/cpm.data";

    if (!directory::has_file(config_location))
        return;

    data_file.open(config_location);

    if (!misc::ifstream_open(data_file))
        return;

    // Nearly identical to project data storage, except information stored in config instead of data
    while (data_file.get(ch))
    {
        if (ch == '\n')
        {
            config[key] = value;
            key = value = "";
            onKey = true;

            prevCh = ch;
            continue;
        }
        else if (prevCh == ':')
        {
            prevCh = ch;
            continue;
        }
        else if (ch == ':')
        {
            onKey = false;
            prevCh = ch;
            continue;
        }

        if (onKey)
        {
            key += ch;
            prevCh = ch;
            continue;
        }

        value += ch;
        prevCh = ch;
        continue;
    }

    config[key] = value;
}

/**
 * @brief Writes to cpm.data from data
 *
 */
void Data_Handler::write()
{
    std::ofstream data_file("cpm.data");

    if (!misc::ofstream_open(data_file))
        return;

    for (const auto &[k, v] : data)
    {
        if (k == "" || v == "")
            continue;

        data_file << k << ": " << v << "\n";
    }

    data_file.close();

    std::string config_location = get_store_location();

    if (!directory::has_directory(config_location))
        return;

    data_file.open(config_location + "/cpm.data");

    for (const auto &[k, v] : config)
    {
        if (k == "" || v == "")
            continue;

        data_file << k << ": " << v << "\n";
    }

    data_file.close();
}

/**
 * @brief Checks if data contains key.
 *
 * @param key
 * @return true
 * @return false
 */
bool Data_Handler::data_has_key(const std::string &key)
{
    if (data.find(key) != data.end())
        return true;

    return false;
}

/**
 * @brief Checks if config contains key.
 * 
 * @param key 
 * @return true 
 * @return false 
 */
bool Data_Handler::config_has_key(const std::string &key)
{
    if (config.find(key) != config.end())
        return true;

    return false;
}