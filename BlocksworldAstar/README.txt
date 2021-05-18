This is a blocksworld problem solver that uses the Astar algorithm.
Problem description is in Blocksworld file
To start the program run 'make clean' in the command line while in directory.
Then run 'make' and './a.out' will still run the program


It will ask you to input the initial state and the final state that is to be reached.
The program detects ; as the creation of a new column. 
Going of the examples giving in the pdf, the initial and final states can be represented as such:

This version requires a text file in order to run
an example is 
3 5 10000
>>>>>>>>>>

DE
ABC
>>>>>>>>>>

CEDA
B
>>>>>>>>>>

the first line denotes the number of columns, number of blocks
the following lines are the initial state and the goal state sepreated by >>>>>...

Constraints: 
MAX_ITERS is set to 100000 by default but can be changed in the BlocksworldAstar.cpp in line 7