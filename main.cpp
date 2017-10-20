#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "Arguments.h"

int main(int argc, char *argv[]) {
    Arguments arguments;

    try {
        arguments.parseArguments(argc, argv);
    }
    catch (const std::exception &exception) {
        std::cerr << exception.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
