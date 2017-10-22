#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "Arguments.h"
#include "IrcBot.h"

using namespace std;

int main(int argc, char *argv[]) {

    try {
        Arguments arguments;
        arguments.parseArguments(argc, argv);

        IrcBot ircBot(&arguments);
        ircBot.start();
    }
    catch (const exception &exception) {
        cerr << exception.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
