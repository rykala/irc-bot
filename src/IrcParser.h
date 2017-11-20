#ifndef ISABOT_IRCPARSER_H
#define ISABOT_IRCPARSER_H

#include <cstring>

using namespace std;

class IrcParser {
public:
    IrcParser() = default;
    ~IrcParser() = default;

    /**
     * Parses a channel name that send a PING command.
     *
     * @param message
     * @return channel name
     */
    string getPingChannels(string message);

    /**
     * Parses a receiver name from a private message ?msg.
     *
     * @param message
     * @return receiver name
     */
    string getPrivateMessageReceiver(string message);

    /**
     * Parses a text of a ?msg.
     *
     * @param message
     * @param receiver
     * @return
     */
    string getPrivateMessageText(string message, string receiver);

    /**
     * Parses a channel name from a IRC message.
     *
     * @param message
     * @return
     */
    string getChannel(string message);

    /**
     * Checks if a IRC message contains given command.
     *
     * @param commandName
     * @param message
     * @return true if the message is of command type, false otherwise
     */
    bool isCommand(string commandName, string message);

    /**
     * Checks if a text of an IRC message contains bot implemented functions either ?msg or ?today.
     *
     * @param command command name
     * @param message
     * @return true if contains, false otherwise
     */
    bool isChatCommand(string command, string message);

    /**
     * Parses users from a NAMES Irc message.
     *
     * @param message
     * @return online users
     */
    string getUsersFromNames(string message);

    /**
     * Parses a channel name from a JOIN Irc message.
     *
     * @param message
     * @return channel name
     */
    string getChannelFromJoin(string message);

    /**
     * Parses a username from a IRC message.
     *
     * @param message
     * @return username
     */
    string getUsername(string message);

    /**
     * Parses a text from a IRC message.
     *
     * @param message
     * @return text of a message
     */
    string getMessageText(string message);

    /**
     * Parses a command from a IRC message.
     *
     * @param message
     * @return command name.
     */
    string getCommand(string message);

private:
    string slicePrefix(string message);
};


#endif //ISABOT_IRCPARSER_H
