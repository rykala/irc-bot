//
// Created by chris on 10/22/17.
//

#ifndef ISABOT_IRCBOT_H
#define ISABOT_IRCBOT_H


#include "TCPClient.h"
#include "Arguments.h"

class IrcBot {
private:
    TCPClient *client;
    Arguments *arguments;

    void setUser(string name);
    void joinChannels(string channels);
    void filterMessages(string message);
    string getDateToday();
    const char * makeMessage(string text);
    bool isCommand(string command, string message);
    string getChannels(string message);
    string getCommand(string message);
    string slicePrefix(string message);


public:
    explicit IrcBot(int argc, char *argv[]);

    ~IrcBot();

    void start();

    string getPingChannels(string message);
};


#endif //ISABOT_IRCBOT_H
