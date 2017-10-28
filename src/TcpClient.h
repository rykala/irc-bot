#ifndef ISABOT_TCPCLIENT_H
#define ISABOT_TCPCLIENT_H

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include "Arguments.h"

using namespace std;

class TcpClient {
private:
    int socket;
    string IP;

    string getIpFromSocket(int socket);

public:
    TcpClient() = default;
    ~TcpClient();

    void send(const char *buffer);
    void receive(char *buffer, size_t size);
    void connect(const char *server, int port);
    string getIP();
};


#endif //ISABOT_TCPCLIENT_H
