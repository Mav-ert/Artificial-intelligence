#include "Node.h"
#include "State.h"
#include <unordered_map>
#include <algorithm>
#include <list>
using namespace std;
const static int MAX_ITERS = 100000;


bool BFS(Node* initial, Node* goal) {
	unordered_map<string, Node*> visited;
	list<Node*> q;
	int goaltests = 0;
	int iterations = 0;
	int maxqsize = 0;
	Node* node = initial;
	if (node->goal_test(goal->getState())) {
		goaltests++;
		node->print_path();
		cout << "Iterations: " << iterations << " Goal Tests:" << goaltests << " max queue size:" << maxqsize <<" Depth: "<< node->getDepth()<<endl;
		return true;
	}
	q.push_back(initial);
	visited.emplace(initial->hash(), initial);
	while (!q.empty()) {
		node = q.front();
		q.pop_front();
		vector<Node*> successors = node->successors();
		for (int i = 0;i < successors.size();i++) {
			State* s = successors[i]->getState();
			if (s->match(goal->getState())){
				cout << "Match found" <<endl;
				successors[i]->print_path();
				cout << "Iterations: " << iterations << " Goal Tests:" << goaltests << " max queue size:" << maxqsize << " Depth:"<<successors[i]->getDepth()<<endl;
				return true;
			}
			else {
				goaltests++;
			}
			if (visited.find(s->hash()) == visited.end()) {
				visited.emplace(successors[i]->hash(), successors[i]);
				q.push_back(successors[i]);
			}
			maxqsize = max(int(q.size()), maxqsize);
		}
		iterations++;
		if (iterations > MAX_ITERS) {
			cout << "Too many iterations:"<<iterations << endl;
			return false;
		}
	}
	cout << "Failed to find match";
	return false;
	
}

int main() {
	string initial = "";
	string goal = "";
	cout << "Input the initial state of the system EX: 'A;BC' (without quotes). If there are empty columns on the edge: 'ABC;' , ';ABC'  or in between:  'A;;BC'" << endl;
	cin >> initial;
	cout << "Input the final state " << endl;
	cin >> goal;
	Node* initialState = new Node(initial);
	Node* goalState = new Node(goal);
	
	BFS(initialState,goalState);
	return 0;
}
