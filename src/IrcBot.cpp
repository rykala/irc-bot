#include <iostream>
#include <sstream>

#include "IrcBot.h"

using namespace std;

IrcBot::IrcBot(int argc, char *argv[]) {
    client = new TCPClient();
    arguments = new Arguments();
    parser = new IrcParser();

    arguments->parseArguments(argc, argv);
}

IrcBot::~IrcBot() {
    delete client;
    delete arguments;
    delete parser;
}

void IrcBot::start() {
    char messageBuffer[512];
    string message;

    client->connect(arguments->getHost().c_str(), arguments->getPort());

    setUser("xrykal00");
    joinChannels(arguments->getChannels());

    while (true) {
        client->receive(messageBuffer, sizeof(messageBuffer));

        filterMessages(messageBuffer);

        memset(messageBuffer, 0, sizeof messageBuffer);
    }
}

void IrcBot::filterMessages(string message) {
    message.pop_back(); // Get rid of \r\n

    if (parser->isCommand("PRIVMSG", message)) {
        string channel = parser->getChannel(message);

        if (parser->isChatCommand("today", message)) {
            sendMessage("PRIVMSG " + channel + " :" + getDateToday());
        } else if (parser->isChatCommand("msg", message)) {
            savePrivateMessage(message, channel);
            sendMessage("NAMES " + channel);
        }
    } else if (parser->isCommand("JOIN", message) && !privateMessages.empty()) {
        sendPrivateMessagesToJoinedUser(message);
    } else if (parser->isCommand("353", message) && privateMessagesCounter) {
        sendMessageToOnlineUser(message);
    } else if (parser->isCommand("366", message) && privateMessagesCounter) {
        privateMessagesCounter--;
    } else if (parser->isCommand("PING", message)) {
        sendMessage("PONG " + parser->getPingChannels(message));
    }
}

void IrcBot::setUser(string name) {
    sendMessage("NICK " + name);
    sendMessage("USER " + name + " " + name + " " + name + " :" + name);
}

void IrcBot::joinChannels(string channels) {
    sendMessage("JOIN " + channels);
}

void IrcBot::sendMessage(string message) {
    message += "\r\n";
    client->send(message.c_str());
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

void IrcBot::savePrivateMessage(string message, string channel) {
    string receiver = parser->getPrivateMessageReceiver(message);
    if (receiver.empty()) {
        return;
    }

    string messageText = parser->getPrivateMessageText(message, receiver);
    if (messageText.empty()) {
        return;
    }

    vector<string> privateMessage = {channel, receiver, messageText};
    privateMessages.push_back(privateMessage);
    privateMessagesCounter++;
}

void IrcBot::sendMessageToOnlineUser(string message) {
    string user;

    string users = parser->getUsersFromNames(message);
    stringstream usersStream(users);

    vector<string> privateMessage = privateMessages.at(privateMessages.size() - privateMessagesCounter);

    while (getline(usersStream, user, ' ')) {
        cout << user << endl;
        if (user == privateMessage[1]) {
            sendMessage("PRIVMSG " + privateMessage[0] + " :" + privateMessage[1] + ':' + privateMessage[2]);
            privateMessages.erase(privateMessages.end() - privateMessagesCounter);
        }
    }
}

void IrcBot::sendPrivateMessagesToJoinedUser(string message) {
    cout << message << endl;
    string joinedChannel = parser->getChannelFromJoin(message);
    string user = parser->getJoinedUserFromJoin(message);
    //todo bad parsing

    for (auto it = privateMessages.begin(); it != privateMessages.end();) {
        vector<string> privateMessage = *it;

        if (joinedChannel == privateMessage[0] && user == privateMessage[1]) {
            sendMessage("PRIVMSG " + privateMessage[0] + " :" + privateMessage[1] + ':' + privateMessage[2]);
            it = privateMessages.erase(it);
        } else {
            it++;
        }
    }
}