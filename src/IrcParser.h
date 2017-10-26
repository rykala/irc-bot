#ifndef ISABOT_IRCPARSER_H
#define ISABOT_IRCPARSER_H

#include <cstring>

using namespace std;

class IrcParser {
public:
    IrcParser() = default;

    ~IrcParser() = default;

    string getPingChannels(string message);

    string getPrivateMessageReceiver(string message);

    string getPrivateMessageText(string message, string receiver);

    string getChannel(string message);

    bool isCommand(string commandName, string message);

    bool isChatCommand(string command, string message);

    string getUsersFromNames(string message);

    string getChannelFromJoin(string message);

    string getJoinedUserFromJoin(string message);

private:
    string slicePrefix(string message);
};


#endif //ISABOT_IRCPARSER_H
