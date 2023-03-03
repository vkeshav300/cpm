#pragma once

namespace directory
{
    bool hasFile(const char *dir, const char *name);

    bool hasFolder(const char *dir, const char *name);

    bool createFile(const char *dir, const char *name);

    bool createFolder(const char *dir, const char *name);
};