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

    /**
     * Sends data from a buffer.
     *
     * @param buffer data to be send
     */
    void send(const char *buffer);

    /**
     * Connects to a server.
     *
     * @param server name of the server, or IPv4 or IPv6 address.
     * @param port port number.
     */
    void connect(const char *server, int port);
};


#endif //ISABOT_UDPCLIENT_H
