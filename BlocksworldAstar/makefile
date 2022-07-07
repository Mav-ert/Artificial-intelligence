CC = g++

all: BlocksworldAstar.exe

BlocksworldAstar.exe: BlocksworldAstar.o State.o Node.o
	g++ BlocksworldAstar.o State.o Node.o

BlocksworldAstar.o: BlocksworldAstar.cpp State.o Node.o
	$(CC) -g -std=c++11 -c BlocksworldAstar.cpp 

State.o: State.cpp State.h
	$(CC) -g -std=c++11 -c State.cpp

Node.o: Node.cpp Node.h 
	$(CC) -g -std=c++11 -c Node.cpp

clean: 
	-rm -f *.o a.exe