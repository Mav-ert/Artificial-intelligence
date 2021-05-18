This is a blocksworld problem solver that uses BFS.
Problem: A BW problem instance is given as 2 states:an initial state and a goal state.  An example is shown below.  The operator for generating moves in this problem can only pick up the top block on any stack and move it to the top of any other stack.  Each action has equal (unit) cost.  The objective is to find a sequence of actions that will transform the initial state into the goal state (preferably with the fewest moves, hence the shortest path to the goal.)  
example

C
B                         A
A           ->         B  C 
_  _  _                _  _  _
initial state          goal state
ABC;;                  B;CA
To start the program run 'make clean' in the command line while in directory.
Then run 'make'. then a.exe or a.out depending on the os


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