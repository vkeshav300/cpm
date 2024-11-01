/**
 * @file directory.cpp
 * @brief Contains most directory-related functions that aren't commands.
 * @version 0.1
 * @date 2023-09-29
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "directory.h"
#include "logger.h"
#include "misc.h"

#include <algorithm>

namespace directory
{
    /**
     * @brief Checks if directory exists at path.
     *
     * @param path
     * @return true
     * @return false
     */
    bool has_directory(const std::filesystem::path &path)
    {
        return std::filesystem::is_directory(std::filesystem::absolute(path));
    }

    /**
     * @brief Checks if file exists at a path.
     *
     * @param file
     * @return true
     * @return false
     */
    bool has_file(const std::filesystem::path &path)
    {
        return std::filesystem::exists(std::filesystem::absolute(path));
    }

    /**
     * @brief Creates directory at path.
     *
     * @param path
     */
    void create_directory(const std::filesystem::path &path)
    {
        if (has_directory(path))
            return;

        std::filesystem::create_directory(std::filesystem::absolute(path));
    }

    /**
     * @brief Create a file at path.
     *
     * @param path
     */
    void create_file(const std::filesystem::path &path)
    {
        if (has_file(path))
            return;

        std::ofstream file(path);
        file.close();
    }

    /**
     * @brief Destroys file at path.
     *
     * @param path
     */
    void destroy_file(const std::filesystem::path &path)
    {
        if (!has_file(path))
            return;

        std::filesystem::remove(std::filesystem::absolute(path));
    }

    /**
     * @brief Returns structure of current directory.
     *
     * @return std::string
     */
    std::string get_structure()
    {
        if (has_directory("src") && has_directory("include"))
            return "default";

        return "simple";
    }

    /**
     * @brief Returns directory default file extension.
     *
     * @return std::string
     */
    std::string get_extension()
    {
        // Get file names in directory
        std::vector<std::string> files;
        const std::filesystem::path current_dir((get_structure() == "default") ? "src/" : "./");
        const std::filesystem::directory_iterator start(current_dir);
        const std::filesystem::directory_iterator end;

        std::transform(start, end, std::back_inserter(files), [](const std::filesystem::directory_entry &entry)
                       { return entry.path().string(); });

        // Check for file extension type
        for (const auto &v : files)
        {
            auto const pos = v.find_last_of(".");
            const std::string leaf = v.substr(pos + 1);

            if (leaf == "cpp")
                return ".cpp";
        }

        return ".c";
    }
} // namespace directory
