#include "commands.h"
#include "directory.h"

#include <iostream>
#include <fstream>

void commands::init(std::string language)
{
    std::string default_folders[4] = {"assets", "src", "src/include", "src/lib"};
    std::string default_files[5] = {".gitignore", "Makefile", "README.md", "LICENSE", "cpm.data"};

    for (std::string folder : default_folders)
        directory::createFolder("./", folder);
    
    std::cout << "Created folders\n";
    
    for (std::string file : default_files)
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

        std::ofstream file_make("./Makefile");
        file_make << "build:\n    g++ -o main main.cpp";
        file_make.close();

        std::ofstream file_cpm("./cpm.data");
        file_cpm << "language: cpp";
        file_cpm.close();
    }
    
    else
        std::cerr << "Error: \'" << language << "\' is a unsupported programming language.\n";

    std::cout << "Created files\n";

    std::ofstream file_ignore("./.gitignore");
    file_ignore << "# Build Artifacts\n.exe\n\n# Other\n.vscode/";
    file_ignore.close();
    
    std::cout << "Written files\n";
}