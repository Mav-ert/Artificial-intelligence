#include "State.h"
#pragma once
#ifndef NODE_H
#define NODE_H
class Node {
private:
	State* nodestate;
	Node* parent=nullptr;
	int depth=0;

public:
	Node(State* state) {
		nodestate = state;
	}


	Node(std::string statestring){
		nodestate = new State(statestring);
	}

	~Node() {
		delete [] nodestate;
		delete[] parent;
	}

	//Returns a new node with the given state
	Node* add(State* state);


	//Sets parent giving a Node*
	void setParent(Node* Parent);


	//Returns Depth. Genereally called when BFS is done for output of statistics
	int getDepth() {
		return depth;
	}


	// checks whether this state matches another (like the goal)
	bool goal_test(State*);



	// gets the successors of the state, and wraps them in Nodes
	std::vector<Node*> successors();
	State* getState();


	std::string hash(); // return hash key of state


	void print_path(); // print sequence of states from root down to this
};
#endif