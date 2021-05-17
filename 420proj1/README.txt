This is a blocksworld problem solver that uses BFS.
THIS IS IMPORTANT
To start the program run 'make clean' in the command line while in directory.
Then run 'make'. If an error pops out saying 
'g++: error: BlocksworldBFS.o: No such file or directory
make: *** [a.out] Error 1' 

It still should have made a working a.out file. I am not sure why its not making the .o file. 
Though the a.out file is made fine so running './a.out' will still run the program


It will ask you to input the initial state and the final state that is to be reached.
The program detects ; as the creation of a new column. 
Going of the examples giving in the pdf, the initial and final states can be represented as such:

test 1: 
initial state: ABC;
final state: ;CBA

test 2: 
intital state: BCF;;A;DE
final state: B;DFC;AE

test 3: 
initial state: EGH;AFI;BJ;C;D
final state: EG;;BJ;;DIFCAH

Make sure no spaces are used when the inputs are given.
Once the inputs are given it should output the states and moves it takes to get 
from the initial state to the final state as well as other information. 
If it fails to find a match or takes too many iterations there will be a failure message and the program should stop.

Constraints: 
MAX_ITERS is set to 100000 by default but can be changed in the BlocksworldBFS.cpp in line 7