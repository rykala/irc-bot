#ifndef ISABOT_TCPCLIENT_H
#define ISABOT_TCPCLIENT_H

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include "Arguments.h"

using namespace std;

class TCPClient {
    int socket;

public:
    TCPClient() = default;
    ~TCPClient();

    ssize_t send(const char *buffer);
    ssize_t receive(char *buffer, size_t len);
    void connect(const char *server, int port);
};


#endif //ISABOT_TCPCLIENT_H
