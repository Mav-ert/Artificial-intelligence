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
};




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




