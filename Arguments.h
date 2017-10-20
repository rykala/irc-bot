#ifndef IRC_BOT_ARGUMENTS_H
#define IRC_BOT_ARGUMENTS_H

#include <string>
#include <getopt.h>
#include <vector>

class Arguments {
public:
    Arguments() = default;

    const std::string &getHost() const {
        return host;
    }

    void setHost(const std::string &host);

    int getPort() const {
        return port;
    }

    void setPort(int port) {
        Arguments::port = port;
    }

    const std::string &getSyslogServer() const {
        return syslogServer;
    }

    void setSyslogServer(const std::string &syslog_server) {
        Arguments::syslogServer = syslog_server;
    }

    const std::vector<std::string> &getChannels() const {
        return channels;
    }

    void setChannels(const std::vector<std::string> &channels) {
        Arguments::channels = channels;
    }

    const std::vector<std::string> &getHighlights() const {
        return highlights;
    }

    void setHighlights(const std::vector<std::string> &highlights) {
        Arguments::highlights = highlights;
    }

    int parseArguments(int argc, char *argv[]);

private:
    std::string host;
    int port = 6667;
    std::vector<std::string> channels;
    std::vector<std::string> highlights;
    std::string syslogServer = "127.0.0.1";

    std::vector<std::string> splitString(const std::string &string, char delimiter);
};


#endif //IRC_BOT_ARGUMENTS_H
