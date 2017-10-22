#include <iostream>
#include <ctime>
#include <chrono>
#include <ctime>

#include "IrcBot.h"

using namespace std;

IrcBot::IrcBot(Arguments *arguments) : arguments(arguments) {
    client = new TCPClient();
}

IrcBot::~IrcBot() {
    delete (client);
}

void IrcBot::start() {
    char message[512];

    client->connect(arguments->getHost().c_str(), arguments->getPort());

    this->setUser("xrykal00");
    this->joinChannels(arguments->getChannels());

    while (true) {
        client->receive(message, sizeof(message));
        cout << message << endl;
        this->filterMessages(message);
    }
}

void IrcBot::setUser(string name) {
    client->send(makeMessage("NICK " + name));
    client->send(makeMessage("USER " + name + " " + name + " " + name + " :" + name));
}

void IrcBot::joinChannels(string channels) {
    client->send(makeMessage("JOIN " + channels));
}

void IrcBot::filterMessages(const char *message) {
    std::size_t found = string(message).find("?today");
    if (found != std::string::npos) {
        client->send(makeMessage("PRIVMSG #xrykal00 :" + this->getDateToday()));
    }
}

const char *IrcBot::makeMessage(string text) {
    string message;
    message = text + "\r\n";

    return message.c_str();
}

string IrcBot::getDateToday() {
    time_t time;
    struct tm *timeInfo;
    char buffer[80];

    time(&time);
    timeInfo = localtime(&time);

    strftime(buffer, 80, "%d.%m.%Y", timeInfo);

    return string(buffer);
}
