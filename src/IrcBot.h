#ifndef ISABOT_IRCBOT_H
#define ISABOT_IRCBOT_H

#include "TcpClient.h"
#include "Arguments.h"
#include "IrcParser.h"
#include "UdpClient.h"


class IrcBot {
private:
    TcpClient *TCPClient;
    UdpClient *UDPClient;
    Arguments *arguments;
    IrcParser *parser;

    vector<vector<string>> privateMessages; // [channelName, receiver, message]
    int privateMessagesCounter = 0;

    void setUser(string name);

    void joinChannels(string channels);

    void filterMessages(string message);

    string getDateToday(int type);

    void sendMessage(string message);


public:
    explicit IrcBot(int argc, char *argv[]);

    ~IrcBot();

    void start();

    void savePrivateMessage(string message, string channel);

    void sendPrivateMessagesToJoinedUser(string message);

    void sendMessageToOnlineUser(string message);

    void logMessage(string message);

    bool containsKeywords(string message) const;

    bool shouldLogMessage(const string message) const;
};


#endif //ISABOT_IRCBOT_H
