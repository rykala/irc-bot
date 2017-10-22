#include <cstring>
#include <netdb.h>
#include <arpa/inet.h>
#include <iostream>

#include "TCPClient.h"

TCPClient::~TCPClient() {
    close(socket);
}

ssize_t TCPClient::send(const char *buffer) {
    return write(socket, buffer, strlen(buffer));
}

ssize_t TCPClient::receive(char *buffer, size_t len) {
    ssize_t index;

    if ((index = recv(socket, buffer, 512, 0)) < 1) {
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
    struct addrinfo hints, *servinfo;

    //Ensure that servinfo is clear
    memset(&hints, 0, sizeof hints); // make sure the struct is empty

    //setup hints
    hints.ai_family = AF_UNSPEC; // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets

    //Setup the structs if error print why
    int res;
    if ((res = getaddrinfo(host, "6667", &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(res));
    }

    //setup the socket
    if ((socket = ::socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1) {
        perror("client: socket");
    }

    //Connect
    if (::connect(socket, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
        close(socket);
        perror("Client Connect");
    }

    //We dont need this anymore
    freeaddrinfo(servinfo);
}
