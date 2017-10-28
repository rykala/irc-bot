#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "IrcBot.h"

using namespace std;

int main(int argc, char *argv[]) {
    try {
        IrcBot ircBot(argc, argv);
        ircBot.start();
    }
    catch (const exception &exception) {
        cerr << exception.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
