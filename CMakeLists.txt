cmake_minimum_required(VERSION 3.8)
project(isabot)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Arguments.cpp Arguments.h)
add_executable(irc-bot ${SOURCE_FILES})