/**
 * @file directory.cpp
 * @brief Contains most directory-related functions that aren't commands
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
     * @brief Checks if directory exists at path
     *
     * @param path Path to check in
     * @return true
     * @return false
     */
    bool has_folder(const std::filesystem::path &path) { return std::filesystem::is_directory(std::filesystem::absolute(path)); }

    /**
     * @brief Checks if file exists at a path
     *
     * @param path Path to check in
     * @return true
     * @return false
     */
    bool has_file(const std::filesystem::path &path) { return std::filesystem::exists(std::filesystem::absolute(path)); }

    /**
     * @brief Creates folder at path for multiple paths
     *
     * @param paths Paths to folders to be created
     */
    void create_folders(const std::vector<std::filesystem::path> &paths)
    {
        for (const auto &path : paths)
            std::filesystem::create_directories(std::filesystem::absolute(path));
    }

    /**
     * @brief Create a file at path
     *
     * @param path Path to file to be created
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
     * @param path Path to file to destroy.
     */
    void destroy_file(const std::filesystem::path &path)
    {
        if (!has_file(path))
            return;

        std::filesystem::remove(std::filesystem::absolute(path));
    }

    /**
     * @brief Get the structure of directory
     *
     * @return std::string
     */
    std::string get_structure()
    {
        if (has_folder("src") & has_folder("include"))
            return "executable";

        return "simple";
    }

    /**
     * @brief Get the file extension of directory
     *
     * @return std::string
     */
    std::string get_extension()
    {
        // Get file names in directory
        std::vector<std::string> files;
        const std::filesystem::path current_dir((get_structure() == "executable") ? "src/" : "./");
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

    /**
     * @brief Gets expected path to header file <name> in directory
     *
     * @param name Name of header file
     * @param hpp If header extension is .hpp
     * @return std::filesystem::path
     */
    std::filesystem::path get_structured_header_path(const std::string &name, const bool &hpp)
    {
        if (get_structure() == "executable")
            return "include/" + name + (hpp ? ".hpp" : ".h");

        return name + (hpp ? ".hpp" : ".h");
    }

    /**
     * @brief Gets expected path to source file <name> in directory
     *
     * @param name Name of source file
     * @return std::filesystem::path
     */
    std::filesystem::path get_structured_source_path(const std::string &name)
    {
        if (get_structure() == "executable")
            return "src/" + name + get_extension();

        return name + get_extension();
    }
} // namespace directory
