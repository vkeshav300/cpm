#pragma once

#include <string>

namespace directory
{
    bool hasFile(std::string dir, std::string filename);

    bool hasFolder(std::string dir, std::string foldername);

    void createFile(std::string dir, std::string filename);

    void createFolder(std::string dir, std::string foldername);
};