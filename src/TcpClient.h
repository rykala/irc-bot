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

    /**
     * Sends data from buffer.
     *
     * @param buffer data to be send.
     */
    void send(const char *buffer);

    /**
     * Reads data into buffer.
     *
     * @param buffer reads data into this buffer
     * @param size size of the buffer
     */
    void receive(char *buffer, size_t size);

    /**
     * Connect to a given address.
     *
     * @param server server name, or its IPv4 IPv6 address
     * @param port
     */
    void connect(const char *server, int port);

    /**
     * Gets a client IPv4 address from a current connection.
     *
     * @return returns IPv4 address as a string.
     */
    string getIP();
};


#endif //ISABOT_TCPCLIENT_H
