CC = g++

all: a.out

a.out: sammys.o NatDed.o parser.o
	g++ sammys.o NatDed.o parser.o

sammys.o: sammys.cpp NatDed.o parser.o
	$(CC) -g -std=c++11 sammys.cpp NatDed.o parser.o

NatDed.o: NatDed.cpp NatDed.hpp
	$(CC) -g -std=c++11 -c NatDed.cpp

parser.o: parser.cpp parser.hpp
	$(CC) -g -std=c++11 -c parser.cpp

clean: 
	rm -f *.o a.out