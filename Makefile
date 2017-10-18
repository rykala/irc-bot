CPPFLAGS=-std=c++11 -Wall -pedantic -Wextra -g
CPPFLAGS_DEBUG=-std=c++11 -Wall -pedantic -Wextra -g -DDEBUG
CPP=g++

all: irc-bot

debug: client-debug

irc-bot: main.cpp
		$(CPP) $(CPPFLAGS) main.cpp -o irc-bot -lcrypto

client-debug: main.cpp
		$(CPP) $(CPPFLAGS_DEBUG) main.cpp -o irc-bot -lcrypto

pack: clean
	    tar cvzf xrykal00.tgz main.cpp main.h Makefile

clean:
		rm -f irc-bot
		rm -f xrykal00.tgz

clear:
		clean
