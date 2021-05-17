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

Once program starts give the file name ex:D:/artificialintelligence/testfiles/bwchp40.bwp and it should run.

Constraints: 
MAX_ITERS is set to 100000 by default but can be changed in the BlocksworldAs.cpp in line 7