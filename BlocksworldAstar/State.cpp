#include "State.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <string>
using namespace std;

void State::print() {

	for (int i = 0; i < blocksstate.size();i++) {
		for (int j = 0;j < blocksstate.at(i).size();j++) {
			cout << blocksstate.at(i)[j] << " ";
		}
		cout << endl;
	}
};
bool State::match(State* test) {
	for (int i = 0; i < test->blocksstate.size();i++) {
		if (test->blocksstate.at(i) != blocksstate.at(i)) {
			return false;
		}
	}
	return true;
};


string State::hash() {
	if (statestring == "") {
		for (int i = 0; i < blocksstate.size();i++) {
			for (int j = 0;j < blocksstate.at(i).size();j++) {
				statestring.push_back(blocksstate[i][j]);
			}
			if (i != blocksstate.size() - 1) {
				statestring.push_back(';');
			}
		}
	}
	return statestring;
}

static bool isIn(char c, const vector<char>& st) {
	for (char cc : st) if (cc == c) return true;
	return false;
}

float State::heuristic(State& goal) {
	float h1 = 0.0;  
	vector<vector<char>> goalstate = goal.getblocksstate();
	for (int i = 0;i < blocksstate.size();i++) {
		int x = blocksstate.at(i).size() - goalstate.at(i).size();
		h1 += abs(x); // add 1 for each block it has more or less than the goal state
	}
	for (int i = 0;i < blocksstate.size();i++){
		for (int j = 0;j < blocksstate.at(i).size();j++) {
			if (goalstate[i].size() > j) {
				if (goalstate[i].size() <= j || blocksstate[i][j] != goalstate[i][j]) {
					if (isIn(blocksstate.at(i).at(j), goalstate.at(i))) {
						h1 += 2; //block is in wrong spot but right column
					}
					else {
						h1 += 1; // block is in wrong spot and column
					}
				}
				if ((blocksstate[i][j] == goalstate[i][j]) && (i != 0) && (j != 0)) {
					if (blocksstate[i][j - 1] != goalstate[i][j - 1]) {
						h1 += 5; //if block has to move due to block below it not being in right spot
					}
				}
			}
		}
	}
	cout<< h1<<endl;
	return h1;
}


vector<State*>  State::successors() {
	vector<State*> successors;
	vector<vector<char>> save=blocksstate;
	for (int i = 0;i < blocksstate.size();i++) {
		for (int j = 0;j < blocksstate.size();j++) {
			if (i != j) {
				if (blocksstate.at(i).empty() && blocksstate.at(j).empty()) {
					;
				}
				else if (blocksstate.at(i).empty()) {
					blocksstate.at(i).push_back(blocksstate.at(j).at(blocksstate.at(j).size() - 1));
					blocksstate.at(j).pop_back();
				}
				else if (blocksstate.at(j).empty()) {
					blocksstate.at(j).push_back(blocksstate.at(i).at(blocksstate.at(i).size() - 1));
					blocksstate.at(i).pop_back();
				} 
				else {
					blocksstate.at(i).push_back(blocksstate.at(j).at(blocksstate.at(j).size() - 1));
					blocksstate.at(j).pop_back();
				}
				successors.push_back(new State(blocksstate));
				blocksstate.clear();
				blocksstate = save;

			}
		}
	}
	
	blocksstate = save;
	return successors;
}




