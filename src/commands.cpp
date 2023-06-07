#include "commands.h"
#include "directory.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>

void commands::init(std::string language)
{
    std::string default_folders[4] = {"assets", "src", "src/include", "src/lib"};
    std::string default_files[5] = {".gitignore", "Makefile", "README.md", "LICENSE", ".cpm"};

    for (auto &folder : default_folders)
        directory::createFolder("./", folder);

    for (auto &file : default_files)
        directory::createFile("./", file);

    if (language == "c")
    {
        directory::createFile("./", "main.c");

        std::ofstream file_main("./main.c");
        file_main << "#include <iostream>\n\nint main(int argc, char *argv[])\n{\n    std::cout << \"Hello World!\" << std::endl;\n\n    return 0;\n}";
        file_main.close();

        std::ofstream file_make("./Makefile");
        file_make << "build:\n    gcc -o main main.c";
        file_make.close();

        std::ofstream file_cpm("./cpm.data");
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
        std::cerr << "\x1b[0;31m"
                  << "Error: \'" << language << "\' is a unsupported programming language\n"
                  << "\x1b[0m";

    std::ofstream file_ignore("./.gitignore");
    file_ignore << "# Build Artifacts\n.exe\n\n# Other\n.vscode/";
    file_ignore.close();

    std::cout << "\x1b[0;33m"
              << "Note: To edit the name of the executable (typically .exe) file, go into the Makefile and change the placeholder that reads \'executable_name\'.\n"
              << "\x1b[0m";
}

bool commands::verify_init()
{
    if (directory::hasFile("./", ".cpm"))
        return true;

    return false;
}

int commands::install(std::string link)
{
    // * Verifies src/include and src/lib have been created (if not creates them)
    if (!directory::hasFolder("./", "src/include"))
        directory::createFolder("./", "src/include");

    if (!directory::hasFolder("./", "src/lib"))
        directory::createFolder("./", "src/lib");

    // * Verifies makefile has -Isrc/Include -Lsrc/lib (if not adds them)
    if (!directory::hasFile("./", "Makefile"))
        return 1;

    std::ifstream *mf;
    mf->open("./Makefile");

    std::string *mf_contents;
    directory::slurp(*mf, mf_contents);

    if (!directory::hasContents(*mf_contents, "-Isrc/Include -Lsrc/lib") && !directory::hasContents(*mf_contents, "-Lsrc/lib -Isrc/Include"))
    {
        
    }

    // TODO --> Verifies github link is valid (if not throws an error)

    std::cout << "\x1b[0;32m"
              << "Checks completed\n"
              << "\x1b[0m";
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