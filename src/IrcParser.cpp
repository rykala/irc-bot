#include <iostream>

#include "IrcParser.h"

using namespace std;

bool IrcParser::isCommand(string commandName, string message) {
    string command;
    size_t commandLength;
    string nullString;

    if (commandName != "PING") {
        message = slicePrefix(message);
    }

    commandLength = message.find(' ');
    if (commandLength == string::npos) {
        return false;
    }

    command = message.substr(0, commandLength);

    return (command == commandName);
}

string IrcParser::slicePrefix(string message) {
    size_t prefixEnd;
    string nullString;

    prefixEnd = message.find(' ');
    if (prefixEnd == string::npos) {
        return nullString;
    }

    message = message.substr(prefixEnd + 1, message.length());

    return message;
}

bool IrcParser::isChatCommand(string command, string message) {
    size_t todayCommandStart;
    string todayCommand;

    message = slicePrefix(message);
    command = "?" + command;

    todayCommandStart = message.find(" :");
    if (todayCommandStart == string::npos) {
        return false;
    }

    todayCommandStart += 2; // need to add the " :"
    todayCommand = message.substr(todayCommandStart, (command + " ").length());

    return (todayCommand == command || todayCommand == (command + " "));
}

string IrcParser::getChannel(string message) {
    string nullString;
    string channels;
    size_t channelsStart;
    size_t channelsEnd;

    message = slicePrefix(message);

    channelsStart = message.find(' ');
    if (channelsStart == string::npos) {
        return nullString;
    }

    channels = message.substr(channelsStart + 1, message.length());

    channelsEnd = channels.find(' ');
    if (channelsEnd == string::npos) {
        return nullString;
    }

    channels = channels.substr(0, channelsEnd);

    return channels;
}

string IrcParser::getPingChannels(string message) {
    string channels = message.substr(message.find(' ') + 1, message.length());

    return channels;
}

string IrcParser::getPrivateMessageReceiver(string message) {
    string receiver;
    string nullString;
    size_t receiverStart;
    size_t receiverEnd;
    string command = ":?msg ";

    message = slicePrefix(message);

    receiverStart = message.find(":?msg ");
    if (receiverStart == string::npos) {
        return nullString;
    }

    receiver = message.substr(receiverStart + command.length(), message.length());

    receiverEnd = receiver.find(':');
    if (receiverEnd == string::npos) {
        return nullString;
    }

    receiver = receiver.substr(0, receiverEnd);

    return receiver;
}

string IrcParser::getPrivateMessageText(string message, string receiver) {
    string messageText;
    size_t messageStart;
    string nullString;

    message = slicePrefix(message);

    messageStart = message.find(receiver + ':');
    if (messageStart == string::npos) {
        return nullString;
    }

    messageStart += (receiver.length() + 1);

    messageText = message.substr(messageStart, message.length());

    return messageText;
}

string IrcParser::getUsersFromNames(string message) {
    string users;
    size_t usersStart;

    usersStart = message.find(" :");
    if (usersStart == string::npos) {
        return users;
    }

    usersStart += string(" :").length();
    users = message.substr(usersStart, message.length());

    return users;
}

string IrcParser::getChannelFromJoin(string message) {
    string join = "JOIN ";
    return message.substr(message.find(join) + join.length(), message.length());
}

string IrcParser::getUsername(string message) {
    return message.substr(1, message.find('!') - 1);
}

string IrcParser::getMessageText(string message) {
    string text;

    text = message.substr(message.find(' '), message.length());
    text = text.substr(text.find(" :") + 2, text.length());

    return text;
}
