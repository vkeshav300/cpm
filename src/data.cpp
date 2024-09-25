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
#include "logger.h"

#include <fstream>

/**
 * @brief Get method for DATA_HANDLER singleton class.
 * 
 * @return Data_Handler& 
 */
Data_Handler &Data_Handler::get()
{
    static Data_Handler data_handler;
    return data_handler;
}

/**
 * @brief Reads cpm.data file and stores it in data.
 * 
 */
void Data_Handler::read()
{
    std::ifstream data_file("cpm.data");

    if (!data_file.is_open())
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
}

/**
 * @brief Writes to cpm.data from data
 * 
 */
void Data_Handler::write()
{
    std::ofstream data_file("cpm.data");

    if (!data_file.is_open())
        return;

    for (const auto &[k, v] : data)
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
bool Data_Handler::has_key(std::string key)
{
    if (data.find(key) != data.end())
        return true;

    return false;
}