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

    /*
     * Sends a message to a IRC server to set nickname, username, hostname, servername a realname.
     */
    void setUser(string name);

    /*
     * Sends a message to a IRC server to join given channels.
     */
    void joinChannels(string channels);

    /*
     * Filters received IRC messages and calls a given action upon them.
     */
    void filterMessages(string message);

    /*
     * Gets today's date in format for either IRC or SYSLOG protocol.
     */
    string getDateToday(int type);

    /*
     * Sends a message using TCP client.
     */
    void sendMessage(string message);


public:
    explicit IrcBot(int argc, char *argv[]);
    ~IrcBot();

    /**
     * Starts a bot.
     */
    void start();

    /**
     * Saves a private message to a user in an attribute privateMessages.
     *
     * @param message
     * @param channel name of the channel the message was send on
     */
    void savePrivateMessage(string message, string channel);

    /**
     * Sends saved private messages to a joined user, if he has any.
     *
     * @param message
     */
    void sendPrivateMessagesToJoinedUser(string message);

    /**
     * If a currently saved message is saved and recipient is online, sends him this message.
     *
     * @param message
     */
    void sendMessageToOnlineUser(string message);

    /**
     * Sends a SYSLOG to a server to log the message.
     *
     * @param message
     */
    void logMessage(string message);

    /**
     * Check if message contains keywords from highlights attribute.
     *
     * @param message
     * @return true if contains keywords, false otherwise
     */
    bool containsKeywords(string message) const;

    /**
     * Determines if current message should be logged.
     *
     * @param message
     * @return true if the message should be logged, false otherwise
     */
    bool shouldLogMessage(const string message) const;

    /**
     * Check if IRC message is an error message.
     *
     * @param message
     * @return true if the message is error, false otherwise
     */
    bool isError(string message);
};


#endif //ISABOT_IRCBOT_H
