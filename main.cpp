#include "src/commands.h"

#include <iostream>

int main(int argc, char *argv[])
{
    unsigned int success = commands::process(argv[1], argv[2]);

    if (success == 0)
    {
        std::cout << "Finished task \"" << argv[1] << "\" with argument \"" << argv[2] << "\" successfully [" << success << "]" << std::endl;
    }
    else
    {
        std::cout << "Finished task \"" << argv[1] << "\" with argument \"" << argv[2] << "\" unsuccessfully [" << success << "]" << std::endl;
    }

    return success;
}