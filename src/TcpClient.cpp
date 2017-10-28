#include <cstring>
#include <netdb.h>
#include <iostream>
#include <arpa/inet.h>
#include <stdexcept>

#include "TcpClient.h"

TcpClient::~TcpClient() {
    if (socket) {
        close(socket);
    }
}

void TcpClient::send(const char *buffer) {
    if (write(socket, buffer, strlen(buffer)) < 0) {
        throw runtime_error("Error writing to socket.");
    }
}

void TcpClient::receive(char *buffer, size_t size) {
    ssize_t index;

    if ((index = recv(socket, buffer, size, 0)) < 1) {
        throw runtime_error("Error: invalid read from socket.");
    }

    // CLEARS rubbish from received message
    buffer[index] = '\0';
    if (buffer[index - 1] == '\n') {
        buffer[index - 1] = '\0';
    }
}

void TcpClient::connect(const char *host, int port) {
    struct addrinfo address, *addressInfo; // NOLINT

    // INITIALIZE ADDR STRUCT
    memset(&address, 0, sizeof address);
    address.ai_family = AF_INET;
    address.ai_protocol = IPPROTO_TCP;
    address.ai_socktype = SOCK_STREAM;

    const char *portString = to_string(port).c_str();

    if (getaddrinfo(host, portString, &address, &addressInfo) != 0) {
        throw runtime_error("Error: Invalid address.");
    }

    if ((socket = ::socket(addressInfo->ai_family, addressInfo->ai_socktype, addressInfo->ai_protocol)) == -1) {
        throw runtime_error("Error: Could not create socket.");
    }

    if (::connect(socket, addressInfo->ai_addr, addressInfo->ai_addrlen) == -1) {
        throw runtime_error("Error: could not connect.");
    }

    freeaddrinfo(addressInfo);
}

string TcpClient::getIP() {
    if (IP == "") {
        IP = getIpFromSocket(socket);
    }

    return IP;
}

string TcpClient::getIpFromSocket(int socket) {
    struct sockaddr pV4Addr;
    string ip;
    socklen_t addressLength = sizeof(pV4Addr);

    getsockname(socket, &pV4Addr, &addressLength);
    struct sockaddr_in *addressInternet;
    addressInternet = (sockaddr_in *)(&pV4Addr);

    ip = inet_ntoa(addressInternet->sin_addr);

    return ip;
}
