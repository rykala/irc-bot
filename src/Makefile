PROJ=isabot

CPPFLAGS=-std=c++11 -Wall -pedantic -Wextra -g
CPPFLAGS_DEBUG=-std=c++11 -Wall -pedantic -Wextra -g -DDEBUG
CPP=g++

SRC_FILES=$(wildcard *.cpp)
HEADERS=$(wildcard *.h)
OBJ_FILES=$(patsubst %.cpp, %.o, $(SRC_FILES))

all: isabot

isabot: $(OBJ_FILES)
		$(CPP) $(CPPFLAGS) $^ -o $(PROJ)
		rm -f *.o

clean:
		rm -f *.o
		rm -f isabot
