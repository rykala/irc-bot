#include <cstring>
#include <netdb.h>
#include <iostream>
#include <stdexcept>
#include "UdpClient.h"

using namespace std;

UdpClient::~UdpClient() {
    delete serverAddress;
}

void UdpClient::connect(const char *server, int port) {
    struct addrinfo address; // NOLINT

    const char *portString = to_string(port).c_str();

    // INITIALIZE ADDR STRUCT
    memset(&address, 0, sizeof address);
    address.ai_family = AF_INET;
    address.ai_protocol = IPPROTO_UDP;
    address.ai_socktype = SOCK_DGRAM;

    if (getaddrinfo(server, portString, &address, &serverAddress) != 0) {
        throw runtime_error("Error: Invalid address.");
    }

    if ((socket = ::socket(serverAddress->ai_family, serverAddress->ai_socktype, serverAddress->ai_protocol)) == -1) {
        throw runtime_error("Error: Could not create socket.");
    }
}

void UdpClient::send(const char *buffer) {
    if (sendto(socket, buffer, strlen(buffer), 0, serverAddress->ai_addr, serverAddress->ai_addrlen) == -1) {
        throw runtime_error("Error writing to socket.");
    }
}
