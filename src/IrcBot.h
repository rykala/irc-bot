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
    void filterMessages(const char *message);


public:
    explicit IrcBot(Arguments *arguments);
    ~IrcBot();
    void start();

    string getDateToday();

    const char * makeMessage(string text);
};


#endif //ISABOT_IRCBOT_H
