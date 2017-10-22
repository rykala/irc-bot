#ifndef IRC_BOT_ARGUMENTS_H
#define IRC_BOT_ARGUMENTS_H

#include <string>
#include <getopt.h>
#include <vector>

using namespace std;

class Arguments {
private:
    string host;
    int port = 6667;
    string channels;
    vector<string> highlights;
    string syslogServer = "127.0.0.1";

    vector<string> splitString(const string &string, char delimiter);

public:
    Arguments() = default;

    void setHost(const string &host);
    int parseArguments(int argc, char *argv[]);

    //Getters
    const string &getHost() const {
        return host;
    }
    int getPort() const {
        return port;
    }
    const string &getChannels() const {
        return channels;
    }
    const vector<string> &getHighlights() const {
        return highlights;
    }
    const string &getSyslogServer() const {
        return syslogServer;
    }
};


#endif //IRC_BOT_ARGUMENTS_H
