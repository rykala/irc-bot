#include <iostream>
#include <ctime>
#include <stdexcept>

#include "IrcBot.h"

using namespace std;

IrcBot::IrcBot(int argc, char *argv[]) {
    client = new TCPClient();
    arguments = new Arguments();

    arguments->parseArguments(argc, argv);
}

IrcBot::~IrcBot() {
    delete client;
    delete arguments;
}

void IrcBot::start() {
    char message[512];

    client->connect(arguments->getHost().c_str(), arguments->getPort());

    this->setUser("xrykal00");
    this->joinChannels(arguments->getChannels());

    while (true) {
        client->receive(message, sizeof(message));
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

void IrcBot::filterMessages(string message) {
    string command;
    string channels;

    message.pop_back(); // Get rid of \r\n
    cout << message << endl;

    if(getCommand(message) == "PING") {
        channels = this->getPingChannels(message);
        client->send(makeMessage("PONG " + channels));
        return;
    }

    message = this->slicePrefix(message);
    command = getCommand(message);

    if (command == "PRIVMSG") {
        channels = this->getChannels(message);

        if (this->isCommand("today", message)) {
            client->send(makeMessage("PRIVMSG " + channels + " :" + this->getDateToday()));
        }
    }
}

string IrcBot::getCommand(string message) {
    string command;
    size_t commandLength;
    string nullString;

    commandLength = message.find(' ');
    if (commandLength == string::npos) {
        return nullString;
    }

    command = message.substr(0, commandLength);

    return command;
}

string IrcBot::slicePrefix(string message) {
    size_t prefixEnd;
    string nullString;

    prefixEnd = message.find(' ');
    if (prefixEnd == string::npos) {
        return nullString;
    }

    message = message.substr(prefixEnd + 1, message.length());

    return message;
}

bool IrcBot::isCommand(string command, string message) {
    size_t todayCommandStart;
    string todayCommand;

    command = "?" + command;

    todayCommandStart = message.find(" :");
    if (todayCommandStart == string::npos) {
        return false;
    }

    todayCommandStart += 2; // need to add the " :"
    todayCommand = message.substr(todayCommandStart, (command + " ").length());

    return (todayCommand == command || todayCommand == (command + " "));
}

string IrcBot::getChannels(string message) {
    string nullString;
    string channels;
    size_t channelsStart;
    size_t channelsEnd;

    channelsStart = message.find(' ');
    if (channelsStart == string::npos) {
        return nullString;
    }

    channels = message.substr(channelsStart + 1, message.length());

    channelsEnd = message.find(' ');
    if (channelsEnd == string::npos) {
        return nullString;
    }

    channels = channels.substr(0, channelsEnd + 1);

    return channels;
}

const char *IrcBot::makeMessage(string text) {
    string message;
    message = text + "\r\n";

    return message.c_str();
}

string IrcBot::getDateToday() {
    time_t t;
    struct tm *timeInfo;
    char buffer[80];

    time(&t);
    timeInfo = localtime(&t);

    strftime(buffer, 80, "%d.%m.%Y", timeInfo);

    return string(buffer);
}

string IrcBot::getPingChannels(string message) {
    string channels = message.substr(message.find(' ') + 1, message.length());

    return channels;
}


// TODO PONG
// TODO ?msg
// TODO SYSLOG