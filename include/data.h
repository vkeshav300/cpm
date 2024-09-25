/**
 * @file data.h
 * @brief Defines Data_Handler singleton.
 * @version 0.1
 * @date 2024-09-15
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <map>
#include <string>

class Data_Handler
{
private:
    Data_Handler() {}

public:
    std::map<std::string, std::string> data;

    Data_Handler(const Data_Handler &obj) = delete;

    static Data_Handler &get();

    void read();

    void write();

    bool has_key(std::string key);
};