cmake_minimum_required(VERSION 3.8)
project(isabot)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/Arguments.cpp src/Arguments.h src/TcpClient.cpp src/TcpClient.h src/IrcBot.cpp src/IrcBot.h src/IrcParser.cpp src/IrcParser.h src/UdpClient.cpp src/UdpClient.h)
add_executable(irc-bot ${SOURCE_FILES})