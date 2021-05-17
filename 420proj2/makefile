CC = g++

all: a.out

a.out: BlocksworldAstar.o State.o Node.o
	g++ BlocksworldS.o State.o Node.o

BlocksworldAstar.o: BlocksworldAstar.cpp State.o Node.o
	$(CC) -g -std=c++11 BlocksworldAstar.cpp State.o Node.o

State.o: State.cpp State.h
	$(CC) -g -std=c++11 -c State.cpp

Node.o: Node.cpp Node.h 
	$(CC) -g -std=c++11 -c Node.cpp

clean: 
	rm -f *.o a.out