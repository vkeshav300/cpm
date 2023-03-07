#include "src/commands.h"

#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char *c_argv[])
{
    std::string argv[argc];

    for (int i = 0; i < argc; i++)
        argv[i] = static_cast<std::string>(c_argv[i]);

    std::cout << "Cast arguments\n";

    if (argv[1] == "init")
        commands::init(argv[2]);
    
    else
        std::cerr << "Error: No command for \'" << argv[1] << "\'" << std::endl;
        return 1;
    
    std::cout << "Finished" << std::endl;

    return 0;
}