CC = g++

all: a.exe

a.exe: resolution.o parser.o
	g++ resolution.o parser.o

resolution.o: resolution.cpp parser.hpp
	$(CC) -g -std=c++11 -c resolution.cpp 

parser.o: parser.cpp parser.hpp
	$(CC) -g -std=c++11 -c parser.cpp

clean: 
	-rm -f *.o a.exe