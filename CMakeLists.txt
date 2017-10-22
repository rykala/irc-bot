cmake_minimum_required(VERSION 3.8)
project(isabot)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/Arguments.cpp src/Arguments.h src/TCPClient.cpp src/TCPClient.h src/IrcBot.cpp src/IrcBot.h)
add_executable(irc-bot ${SOURCE_FILES})