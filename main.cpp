#include "src/commands.h"
#include "src/directory.h"

#include <iostream>

int main(int argc, char *argv[])
{
    directory::createFolder("./", "abcdef123456789");
    directory::createFile("./abcdef123456789/", "test.txt");

    return 0;
}