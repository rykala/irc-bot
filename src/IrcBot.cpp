#include <iostream>
#include <ctime>
#include <stdexcept>
#include <sstream>
#include <cstring>

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
    char messageBuffer[512];
    string message;
    string tmpMessage;

    client->connect(arguments->getHost().c_str(), arguments->getPort());

    setUser("xrykal00");
    joinChannels(arguments->getChannels());

    while (true) {
        client->receive(messageBuffer, sizeof(messageBuffer));
        istringstream messageStream(messageBuffer);

        while (getline(messageStream, message)) {
            filterMessages(message);
        }

        memset(messageBuffer, 0, sizeof messageBuffer);
    }
}

void IrcBot::filterMessages(string message) {
    string command;
    string channels;

    message.pop_back(); // Get rid of \r\n
    cout << message << endl;

    if (getCommand(message) == "PING") {
        channels = getPingChannels(message);
        client->send(makeMessage("PONG " + channels));
        return;
    }

    message = slicePrefix(message);
    command = getCommand(message);

    if (command == "PRIVMSG") {
        channels = getChannels(message);

        if (isCommand("today", message)) {
            client->send(makeMessage("PRIVMSG " + channels + " :" + getDateToday()));
        } else if (isCommand("msg", message)) {
            channels = getChannels(message);
            string receiver = getReceiver(message);
            string messageText = getMessageText(message, receiver);

            array<string, 3> privateMessage = {channels, receiver, messageText};
            messages.push_back(privateMessage);
            privateMessageCounter++;

            client->send(makeMessage("NAMES " + channels));
        }
    } else if (command == "JOIN" && !messages.empty()) {
        channels = getChannels(message);
//        string receiver = getUser(message);

        //todo check if joined user has any messages pending
        // cycle throught messages and send
    } else if (command == "353" && privateMessageCounter) {
        cout << message << endl;
    } else if (command == "366" && privateMessageCounter) {
        privateMessageCounter--;
    }
}

void IrcBot::setUser(string name) {
    client->send(makeMessage("NICK " + name));
    client->send(makeMessage("USER " + name + " " + name + " " + name + " :" + name));
}

void IrcBot::joinChannels(string channels) {
    client->send(makeMessage("JOIN " + channels));
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

    channelsEnd = channels.find(' ');
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

string IrcBot::getReceiver(string message) {
    string receiver;
    string nullString;
    size_t receiverStart;
    size_t receiverEnd;
    string command = ":?msg ";

    receiverStart = message.find(":?msg ");
    if (receiverStart == string::npos) {
        return nullString;
    }

    receiver = message.substr(receiverStart + command.length(), message.length());

    receiverEnd = receiver.find(':');
    if (receiverEnd == string::npos) {
        return nullString;
    }

    receiver = receiver.substr(0, receiverEnd);

    return receiver;
}

string IrcBot::getMessageText(string message, string receiver) {
    string messageText;
    size_t messageStart;
    string nullString;

    messageStart = message.find(receiver + ':');
    if (messageStart == string::npos) {
        return nullString;
    }

    messageStart += (receiver.length() + 1);

    messageText = message.substr(messageStart, message.length());

    return messageText;
}

// TODO ?msg
// TODO SYSLOG