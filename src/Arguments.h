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

    /**
     * Sets host and if host has also specified port, the port is extracted and is set to port attribute sets the port.
     */
    void setHost(const string &host);

    /**
     * Parses arguments of a command line and loads them into class attributes.
     */
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
