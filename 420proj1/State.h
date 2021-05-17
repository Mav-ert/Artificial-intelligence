#pragma once
#ifndef STATE_H
#define STATE_H
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
class State {
private:
	std::vector<std::vector<char>> blocksstate;
	std::string statestring="";
public:
	//Note about the input string
	//if a column is empty the string should specify with a space EX A; ;CB
	State(std::string input) {
		size_t count = std::count(input.begin(), input.end(), ';');
		blocksstate.resize(count + 1);
		int column = 0;
		for (signed int i = 0; i < input.size();i++) {
			if (input[i] == ';') {
				column++;
			}
			else {
				blocksstate.at(column).push_back(input[i]);
			}
		}
		statestring = input;
	};
	//Creates State based on vector representing blockstate
	State(std::vector<std::vector<char>> input) {
		blocksstate = input;
		statestring = this->hash();
	}

	void print(); // for printing out a state (in the horizontal format)
	bool match(State*); // tell whether 2 states are equal, for goal-testing
	std::string hash(); // generate a “key” unique to each state for tracking Visited
	std::vector<State*> successors(); // generate all children of this state given all legal moves
	State* add(std::vector<std::vector<char>> state) {
		State* a = new State(state);
		return a;
	}
};


#endif