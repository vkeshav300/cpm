#pragma once

#include <string>

namespace directory
{
    bool hasFile(std::string , std::string filename);

    bool hasFolder(std::string , std::string foldername);

    void createFile(std::string , std::string filename);

    void createFolder(std::string , std::string foldername);
};