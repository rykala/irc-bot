cmake_minimum_required(VERSION 3.8)
project(irc-bot)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(irc-bot ${SOURCE_FILES})