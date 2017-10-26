#ifndef ISABOT_IRCBOT_H
#define ISABOT_IRCBOT_H

#include "TCPClient.h"
#include "Arguments.h"
#include "IrcParser.h"


class IrcBot {
private:
    TCPClient *client;
    Arguments *arguments;
    IrcParser *parser;

    vector<vector<string>> privateMessages; // [channelName, receiver, message]
    int privateMessagesCounter = 0;

    void setUser(string name);

    void joinChannels(string channels);

    void filterMessages(string message);

    string getDateToday();

    void sendMessage(string message);


public:
    explicit IrcBot(int argc, char *argv[]);

    ~IrcBot();

    void start();

    void savePrivateMessage(string message, string channel);

    void sendPrivateMessagesToJoinedUser(string message);

    void sendMessageToOnlineUser(string message);
};


#endif //ISABOT_IRCBOT_H
