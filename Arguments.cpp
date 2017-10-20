#include <iostream>
#include <stdexcept>
#include <sstream>

#include "Arguments.h"

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
                std::cout << "HELP" << std::endl;
                exit(1);

            case '?':
                throw std::runtime_error("Error: Invalid parameter");

            default:
                break;
        }

        opt = getopt_long(argc, argv, optString, longOpts, &longIndex);
    }

    for (int i = optind; i < argc; i++) {
        if (this->host.empty()) {
            this->setHost(argv[i]);
        } else if (this->channels.empty()) {
            this->setChannels(splitString(argv[i], ','));
        } else {
            throw std::runtime_error("Error: Invalid parameters");
        }
    }

    if (this->host.empty() || this->channels.empty()) {
        throw std::runtime_error("Error: Missing parameters");
    }

    return 0;
}

void Arguments::setHost(const std::string &host) {
    std::string tmpHost = host;
    std::size_t sz;

    std::size_t position = host.find(':');

    if (position != std::string::npos) {
        if (position + 1 == host.length()) {
            throw std::runtime_error("Error: Invalid port");
        }

        tmpHost = host.substr(0, position);

        std::string portString = host.substr(position + 1, host.length());

        int port = std::stoi(portString, &sz);

        if (sz != portString.length() || port < 0) {
            throw std::runtime_error("Error: Invalid port");
        }

        this->port = port;
    }

    this->host = tmpHost;
}

std::vector<std::string> Arguments::splitString(const std::string &string, char delimiter) {
    std::istringstream ss(string);
    std::string token;

    std::vector<std::string> strings;

    while(std::getline(ss, token, delimiter)) {
        strings.push_back(token);
    }

    return strings;
}