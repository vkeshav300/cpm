/**
 * @file data.h
 * @brief Defines Data_Handler singleton
 * @version 0.1
 * @date 2024-09-15
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <unordered_map>
#include <string>

class Data_Handler
{
private:
    Data_Handler() {}

public:
    std::unordered_map<std::string, std::string> config;

    Data_Handler(const Data_Handler &obj) = delete;

    static Data_Handler &get();

    void read();

    void write();

    bool config_has_key(const std::string &key);
};