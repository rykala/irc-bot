#include <iostream>
#include <stdexcept>
#include <sstream>
#include <cstring>

#include "Arguments.h"

using namespace std;

static const char *optString = "s:l:h?";

static const struct option longOpts[] = {
        {"help",  no_argument,       nullptr, 'h'},
        {nullptr, required_argument, nullptr, 's'},
        {nullptr, required_argument, nullptr, 'l'},
        {nullptr, 0,                 nullptr, 0}
};

int Arguments::parseArguments(int argc, char *argv[]) {
    int opt = 0;
    int longIndex = 0;

    opt = getopt_long(argc, argv, optString, longOpts, &longIndex);
    while (opt != -1) {
        switch (opt) {
            case 's':
                this->syslogServer = optarg;
                break;

            case 'l':
                this->highlights = splitString(optarg, ',');
                break;

            case 'h':
                cout << "HELP" << endl;
                exit(1);

            case '?':
                throw runtime_error("Error: Invalid parameter");

            default:
                break;
        }

        opt = getopt_long(argc, argv, optString, longOpts, &longIndex);
    }

    for (int i = optind; i < argc; i++) {
        if (this->host.empty()) {
            this->setHost(argv[i]);
        } else if (this->channels.empty()) {
            this->channels = argv[i];
        } else {
            throw runtime_error("Error: Invalid parameters");
        }
    }

    if (this->host.empty() || this->channels.empty()) {
        throw runtime_error("Error: Missing parameters");
    }

    return 0;
}

void Arguments::setHost(const string &host) {
    string tmpHost = host;
    size_t sz;

    size_t position = host.find(':');

    if (position != string::npos) {
        if (position + 1 == host.length()) {
            throw runtime_error("Error: Invalid port");
        }

        tmpHost = host.substr(0, position);

        string portString = host.substr(position + 1, host.length());

        int port = stoi(portString, &sz);

        if (sz != portString.length() || port < 0) {
            throw runtime_error("Error: Invalid port");
        }

        this->port = port;
    }

    this->host = tmpHost;
}

vector<string> Arguments::splitString(const string &string, char delimiter) {
    istringstream ss(string);
    std::string token;

    vector<std::string> strings;

    while(getline(ss, token, delimiter)) {
        if (token != "") {
            strings.push_back(token);
        }
    }

    return strings;
}
