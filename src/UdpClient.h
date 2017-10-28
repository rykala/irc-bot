//
// Created by chris on 10/28/17.
//

#ifndef ISABOT_UDPCLIENT_H
#define ISABOT_UDPCLIENT_H


class UdpClient {
private:
    int socket;
    struct addrinfo *serverAddress;

public:
    UdpClient() = default;
    ~UdpClient();

    void send(const char *buffer);
    void connect(const char *server, int port);
};


#endif //ISABOT_UDPCLIENT_H
