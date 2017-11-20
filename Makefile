all: isabot

isabot:
		cd src && make && mv isabot ../isabot

pack: clean
	    tar cvzf xrykal00.tar README Makefile manual.pdf src/

clean:
		rm -f isabot
		rm -f xrykal00.tgz
		cd src && make clean

run: isabot
	./isabot irc.freenode.net:6667 "#ISAChannel,#IRC" -s 192.168.0.1 -l "ip,isa"

