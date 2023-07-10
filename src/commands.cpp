#include "commands.h"
#include "directory.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>
#include <vector>

int commands::init(std::string language)
{
    // * All folders and files to be created
    std::vector<std::string> default_folders = {"assets", "src", "src/include", "src/lib"};
    std::vector<std::string> default_files = {".gitignore", "Makefile", "README.md", "LICENSE", ".cpm"};

    // * Create folders and files
    for (auto &folder : default_folders)
        directory::createFolder("./", folder);

    for (auto &file : default_files)
        directory::createFile("./", file);

    // * Fills files with default code
    if (language == "c")
    {
        directory::createFile("./", "main.c");

        std::ofstream file_main("./main.c");
        file_main << "#include <iostream>\n\nint main(int argc, char *argv[])\n{\n    std::cout << \"Hello World!\" << std::endl;\n\n    return 0;\n}";
        file_main.close();

        std::ofstream file_make("./Makefile");
        file_make << "build:\n    gcc -o main main.c ./src/*.c -Isrc/Include -Lsrc/lib";
        file_make.close();

        std::ofstream file_cpm("./.cpm");
        file_cpm << "language: c";
        file_cpm.close();
    }

    else if (language == "cpp" || language == "c++")
    {
        directory::createFile("./", "main.cpp");

        std::ofstream file_main("./main.cpp");
        file_main << "#include <iostream>\n\nint main(int argc, char *argv[])\n{\n    std::cout << \"Hello World!\" << std::endl;\n\n    return 0;\n}";
        file_main.close();

        std::ofstream file_make(default_files[1]);
        file_make << "build:\n    gcc -o main main.cpp ./src/*.cpp -Isrc/Include -Lsrc/lib";
        file_make.close();

        std::ofstream file_cpm(default_files[4]);
        file_cpm << "language: cpp";
        file_cpm.close();
    }

    else
    {
        std::cerr << "\x1b[0;31m"
                  << "Error: \'" << language << "\' is a unsupported programming language\n"
                  << "\x1b[0m";

        return 1;
    }

    std::ofstream file_ignore("./.gitignore");
    file_ignore << "# Build Artifacts\n.exe\n\n# Other\n.vscode/";
    file_ignore.close();

    std::cout << "\x1b[0;33m"
              << "Note: To edit the name of the executable [.exe file], go into the Makefile and change the placeholder that reads \'executable_name\'.\n"
              << "\x1b[0m";

    return 0;
}

bool commands::verify_init()
{
    // * Verifies init has been run
    if (directory::hasFile("./", ".cpm"))
        return true;

    return false;
}

int commands::install(std::string link, std::string tags)
{
    // * Verify src/include and src/lib have been created
    directory::createFolder("./", "src/include");
    directory::createFolder("./", "src/lib");

    // * Verify makefile has -Isrc/Include -Lsrc/lib
    if (!directory::hasFile("./", "Makefile"))
    {
        std::cerr << "\x1b[0;31m"
                  << "Error: Current directory does not contain a Makefile\n"
                  << "\x1b[0m";

        return 2;
    }

    std::ifstream file_make;
    file_make.open("./Makefile");

    std::string mf_contents;
    directory::slurp(file_make, &mf_contents);

    file_make.close();

    if (!directory::hasContents(mf_contents, "-Isrc/Include -Lsrc/lib") && !directory::hasContents(mf_contents, "-Lsrc/lib -Isrc/Include"))
    {
        std::ofstream file_make;
        file_make.open("./Makefile");
        file_make << " -Isrc/Include -Lsrc/lib";
        file_make.close();
    }
    // TODO --> Copy files from github link
    // TODO --> Get library name
    // TODO --> Verify library doesn't already exist (if not "uninstall" files)
    // TODO --> Put files in src/include and src/lib folders as well as adds .dll file to project folder (./)

    return 0;
}

int commands::uninstall(std::string name)
{
    return 0;
}

int commands::file_pair(int method, std::string pair_name, std::string language)
{
    int initialized = static_cast<int>(verify_init());

    directory::createFolder("./", "src");

    if (method == CREATE)
    {
        switch (initialized)
        {
        case 0:
        {
            // * Create files
            if (language == "c" || language == "cpp")
            {
                std::string file_extension = (language == "c") ? ".c" : ".cpp";
                directory::createFile("./src/", pair_name + file_extension);

                {
                    std::ofstream file_pair_main("./src/" + pair_name + file_extension);
                    file_pair_main << "#include \"" + pair_name + ".h\"";
                }
            }
            else
            {
                std::cerr << "\x1b[0;31m"
                          << "Error: \'" << language << "\' is an unsupported programming language\n"
                          << "\x1b[0m";

                return 2;
            }
            break;
        }

        case 1:
        {
            // * Create .h file
            directory::createFile("./src/", pair_name + ".h");

            {
                std::ofstream file_pair_h("./src/" + pair_name + ".h");
                file_pair_h << "#pragma once";
            }

            // * Open and read .cpm file
            std::ifstream file_cpm("./.cpm");
            std::string cpm_contents;
            directory::slurp(file_cpm, &cpm_contents);

            bool found_language = false;
            // * Check for "language:" line
            std::string file_extension;
            if (cpm_contents.find("language: c") != std::string::npos || cpm_contents.find("language: cpp") != std::string::npos)
            {
                found_language = true;
                file_extension = (cpm_contents.find("language: c") != std::string::npos) ? ".c" : ".cpp";
                directory::createFile("./src/", pair_name + file_extension);
            }

            if (!found_language)
            {
                std::cerr << "\x1b[0;31m"
                          << "Error: .cpm file does not contain a valid \'language\' line\n"
                          << "\x1b[0m";
                return 1;
            }

            std::ofstream file_pair_main("./src/" + pair_name + file_extension);
            file_pair_main << "#include \"" + pair_name + ".h\"";
            break;
        }

        default:
            std::cerr << "\x1b[0;31m"
                      << "Error: Unknown error occurred reading initialized status\n"
                      << "\x1b[0m";
            return 3;
        }
    }
    else if (method == DELETE)
    {
        // * Delete files
        // ? Note that this code is confusing because there is no checking of file (or folder) existance. Go to "directory.h" for clarification.
        directory::deleteFile("./src/", pair_name + ".h");
        directory::deleteFile("./src/", pair_name + ".hpp");
        directory::deleteFile("./src/", pair_name + ".c");
        directory::deleteFile("./src/", pair_name + ".cpp");
    }
    else
    {
        std::cerr << "\x1b[0;31m"
                  << "Error: Unknown error occurred reading method status\n"
                  << "\x1b[0m";
        return 4;
    }

    return 0;
}