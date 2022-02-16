CC = g++

all: a.exe

a.exe: BlocksworldBFS.o State.o Node.o
	g++ BlocksworldBFS.o State.o Node.o

BlocksworldBFS.o: BlocksworldBFS.cpp State.o Node.o
	$(CC) -g -std=c++11 -c BlocksworldBFS.cpp State.o Node.o

State.o: State.cpp State.h
	$(CC) -g -std=c++11 -c State.cpp

Node.o: Node.cpp Node.h 
	$(CC) -g -std=c++11 -c Node.cpp

clean: 
	-rm -f *.o a.exe
	