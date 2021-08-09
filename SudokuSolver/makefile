CC = g++

all: a.exe

a.exe: main.o
	g++ main.o

main.o: main.cpp Graph.h 
	$(CC) -g -std=c++11 -c main.cpp 

clean: 
	-del -f *.o a.exe