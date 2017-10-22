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

public:
    explicit IrcBot(Arguments *arguments);
    void start();
};


#endif //ISABOT_IRCBOT_H
