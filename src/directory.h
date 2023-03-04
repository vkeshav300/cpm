#pragma once

namespace directory
{
    bool hasFile(const char *dir, const char *filename);

    bool hasFolder(const char *dir, const char *foldername);

    void createFile(const char *dir, const char *filename);

    void createFolder(const char *dir, const char *foldername);
};