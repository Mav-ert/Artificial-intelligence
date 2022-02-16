CC = g++

all: a.exe

a.exe: DPLL.o parser.o
	g++ DPLL.o parser.o

DPLL.o: DPLL.cpp DPLL.h parser.o
	$(CC) -g -std=c++11 -c DPLL.cpp DPLL.h parser.o

parser.o: parser.cpp parser.hpp
	$(CC) -g -std=c++11 -c parser.cpp

clean: 
	-rm -f *.o a.exe