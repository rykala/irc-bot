PROJ=isabot

CPPFLAGS=-std=c++11 -Wall -pedantic -Wextra -g
CPPFLAGS_DEBUG=-std=c++11 -Wall -pedantic -Wextra -g -DDEBUG
CPP=g++

SRC_FILES=$(wildcard *.cpp)
HEADERS=$(wildcard *.h)
OBJ_FILES=$(patsubst %.cpp, %.o, $(SRC_FILES))

all: isabot

debug: client-debug

isabot: $(OBJ_FILES)
		$(CPP) $(CPPFLAGS) $^ -o $(PROJ) -lcrypto
		rm *.o

client-debug: main.cpp
		$(CPP) $(CPPFLAGS_DEBUG) main.cpp -o isabot -lcrypto

pack: clean
	    tar cvzf xrykal00.tgz main.cpp main.h Makefile

clean:
		rm -f isabot
		rm -f xrykal00.tgz

clear:
		clean
