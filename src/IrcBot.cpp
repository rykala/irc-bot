#include <iostream>
#include "IrcBot.h"

using namespace std;

IrcBot::IrcBot(Arguments *arguments) : arguments(arguments) {
    client = new TCPClient();
}

void IrcBot::start() {
    string message;
    char line[512];

    client->connect(arguments->getHost().c_str(), arguments->getPort());

    if (client->send("NICK xrykal00\r\n") != 0) {
        cout << "SUCCESS" << endl;
    }

    if (client->send("USER xrykal00 xrykal00 xrykal00 :xrykal00\r\n") != 0) {
        cout << "SUCCESS" << endl;
    }

    if (client->send("JOIN #freenode\r\n") != 0) {
        cout << "SUCCESS" << endl;
    }

    while (true) {
        client->receive(line, sizeof(line));
        cout << line << endl;
    }
}
