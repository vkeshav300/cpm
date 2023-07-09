#include "commands.h"
#include "directory.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>

enum eFileMethods : std::size_t
{
    CREATE = 0,
    DELETE
};

int commands::init(std::string language)
{
    // * All folders and files to be created
    std::string default_folders[4] = {"assets", "src", "src/include", "src/lib"};
    std::string default_files[5] = {".gitignore", "Makefile", "README.md", "LICENSE", ".cpm"};

    // * Creates folders and files
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
        file_make << "build:\n    gcc -o main main.c";
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
        file_make << "build:\n    g++ -o executable_name main.cpp";
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
    // * Verifies src/include and src/lib have been created
    if (!directory::hasFolder("./", "src/include"))
        directory::createFolder("./", "src/include");

    if (!directory::hasFolder("./", "src/lib"))
        directory::createFolder("./", "src/lib");

    // * Verifies makefile has -Isrc/Include -Lsrc/lib
    if (!directory::hasFile("./", "Makefile"))
    {
        std::cerr << "\x1b[0;31m"
                  << "Error: Current directory does not contain a Makefile\n"
                  << "\x1b[0m";

        return 1;
    }

    std::ifstream file_make;
    file_make.open("./Makefile");

    std::string *mf_contents;
    directory::slurp(file_make, mf_contents);

    file_make.close();

    if (!directory::hasContents(*mf_contents, "-Isrc/Include -Lsrc/lib") && !directory::hasContents(*mf_contents, "-Lsrc/lib -Isrc/Include"))
    {
        std::ofstream file_make;
        file_make.open("./Makefile");
        file_make << " -Isrc/Include -Lsrc/lib";
        file_make.close();
    }
    // TODO --> Copies files from github link
    // TODO --> Gets library name
    // TODO --> Verifies library doesn't already exist (if not "uninstall" files)
    // TODO --> Puts files in src/include and src/lib folders as well as adds .dll file to project folder (./)

    return 0;
}

int commands::uninstall(std::string name)
{
    return 0;
}

int commands::file_pair(int method, std::string language)
{
    // int initialized = (int)verify_init();

    // switch (method)
    // {
    // case CREATE:
    //     switch (initialized)
    //     {
    //     case 1:
    //         std::ifstream file_cpm;
    //         file_cpm.open("./.cpm");

    //         std::string *cpm_contents;
    //         directory::slurp(file_cpm, cpm_contents);
    //     }
    // }

    return 0;
}