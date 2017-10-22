#include <cstring>
#include <netdb.h>
#include <iostream>

#include "TCPClient.h"

TCPClient::~TCPClient() {
    close(socket);
}

ssize_t TCPClient::send(const char *buffer) {
    return write(socket, buffer, strlen(buffer));
}

void TCPClient::receive(char *buffer, size_t size) {
    ssize_t index;
    if (( index = recv(socket, buffer, size, 0)) < 1) {
        perror("Recv error");
        close(socket);
        exit(1);
    }

    // CLEARS rubbish from received message
    buffer[index] = '\0';
    if (buffer[index - 1] == '\n') {
        buffer[index - 1] = '\0';
    }
}

void TCPClient::connect(const char *host, int port) {
    struct addrinfo address, *addressInfo; // NOLINT

    // INITIALIZE ADDR STRUCT
    memset(&address, 0, sizeof address);
    address.ai_family = AF_UNSPEC;
    address.ai_socktype = SOCK_STREAM;
    address.ai_protocol = IPPROTO_TCP;

    //Setup the structs if error print why
    const char *portString = to_string(port).c_str();

    if (getaddrinfo(host, portString, &address, &addressInfo) != 0) {
        fprintf(stderr, "getaddrinfo");
    }

    //setup the socket
    if ((socket = ::socket(addressInfo->ai_family, addressInfo->ai_socktype, addressInfo->ai_protocol)) == -1) {
        perror("client: socket");
    }

    //Connect
    if (::connect(socket, addressInfo->ai_addr, addressInfo->ai_addrlen) == -1) {
        close(socket);
        perror("Client Connect");
    }

    freeaddrinfo(addressInfo);
}
