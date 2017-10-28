#include <iostream>
#include <sstream>

#include "IrcBot.h"

using namespace std;

#define IRC_DATE 0
#define SYSLOG_DATE 1

IrcBot::IrcBot(int argc, char *argv[]) {
    TCPClient = new TcpClient();
    UDPClient = new UdpClient();
    arguments = new Arguments();
    parser = new IrcParser();

    arguments->parseArguments(argc, argv);
}

IrcBot::~IrcBot() {
    delete TCPClient;
    delete UDPClient;
    delete arguments;
    delete parser;
}

void IrcBot::start() {
    char messageBuffer[512];

    if (!arguments->getHighlights().empty()) {
        UDPClient->connect(arguments->getSyslogServer().c_str(), 514);
    }

    TCPClient->connect(arguments->getHost().c_str(), arguments->getPort());

    setUser("xrykal00");
    joinChannels(arguments->getChannels());

    while (true) {
        TCPClient->receive(messageBuffer, sizeof(messageBuffer));
        filterMessages(messageBuffer);
        memset(messageBuffer, 0, sizeof messageBuffer);
    }
}

void IrcBot::filterMessages(string message) {
    message.pop_back(); // Get rid of \r\n
    cout << message << endl;
    if (parser->isCommand("PRIVMSG", message)) {
        string channel = parser->getChannel(message);

        if (parser->isChatCommand("today", message)) {
            sendMessage("PRIVMSG " + channel + " :" + getDateToday(IRC_DATE));
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

    if (shouldLogMessage(message) && containsKeywords(message)) {
        logMessage(message);
    }
}

bool IrcBot::shouldLogMessage(const string message) const {
    return !arguments->getHighlights().empty() &&
           (parser->isCommand("PRIVMSG", message) || parser->isCommand("NOTICE", message));
}

bool IrcBot::containsKeywords(string message) const {
    string word;

    string text = parser->getMessageText(message);
    stringstream wordsStream(text);

    while (getline(wordsStream, word, ' ')) {
        for (const string &keyword: arguments->getHighlights()) {
            if (keyword == word) {
                return true;
            }
        }
    }

    return false;
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
    TCPClient->send(message.c_str());
}

string IrcBot::getDateToday(int type) {
    time_t t;
    struct tm *timeInfo;
    char buffer[80];

    time(&t);
    timeInfo = localtime(&t);

    if (type == IRC_DATE) {
        strftime(buffer, 80, "%d.%m.%Y", timeInfo);
    } else if (type == SYSLOG_DATE) {
        strftime(buffer, 80, "%b %e %H:%M:%S", timeInfo);
    }

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

    vector<string> privateMessage = privateMessages[privateMessages.size() - privateMessagesCounter];

    while (getline(usersStream, user, ' ')) {
        if (user[0] == '@' || user[0] == '+') {
            user.erase(0, 1); //removes first char
        }

        if (user == privateMessage[1]) {
            sendMessage("PRIVMSG " + privateMessage[0] + " :" + privateMessage[1] + ':' + privateMessage[2]);
            privateMessages.erase(privateMessages.end() - privateMessagesCounter);
        }
    }
}

void IrcBot::sendPrivateMessagesToJoinedUser(string message) {
    string joinedChannel = parser->getChannelFromJoin(message);
    string user = parser->getUsername(message);

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

void IrcBot::logMessage(string message) {
    string syslog = "<134>" + getDateToday(SYSLOG_DATE) + " " + TCPClient->getIP() + " isabot "
                    + parser->getUsername(message) + ": " + parser->getMessageText(message);

    UDPClient->send(syslog.c_str());
}
