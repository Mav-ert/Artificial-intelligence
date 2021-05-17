#include "Node.h"
#include "State.h"
#include <unordered_map>
#include <algorithm>
#include <list>
#include <fstream>
#include <queue>
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
struct comp_nodes {
	State* goal;

	explicit comp_nodes( State& goal):
		goal(&goal) { }
	bool operator()(Node* a, Node* b){
		return a->hueristic(*goal) > b->hueristic(*goal);
	}
};
bool Astar(Node* initial, Node* goal) {
	comp_nodes k(*goal->getState());
	priority_queue<Node*,vector<Node*>, comp_nodes> pq(k);
	unordered_map<string, Node*> visited;
	int goaltests = 0;
	int iterations = 0;
	int maxqsize = 0;
	Node* node = initial;
	if (node->goal_test(goal->getState())) {
		goaltests++;
		node->print_path();
		cout << "Iterations: " << iterations << " max queue size:" << maxqsize << " Depth: " << node->getDepth() << endl;
		return true;
	}
	pq.push(initial);
	visited.emplace(initial->hash(), initial);
	while (!pq.empty()) {
		node = pq.top();
		pq.pop();
		vector<Node*> successors = node->successors();
		for (int i = 0;i < successors.size();i++) {
			State* s = successors[i]->getState();
			if (s->match(goal->getState())) {
				cout << "Match found" << endl;
				successors[i]->print_path();
				cout << "Iterations: " << iterations << " max queue size:" << maxqsize << " Depth:" << successors[i]->getDepth() << endl;
				return true;
			}
			else {
				goaltests++;
			}
			if (visited.find(s->hash()) == visited.end()) {
				visited.emplace(successors[i]->hash(), successors[i]);
				pq.push(successors[i]);
			}
			maxqsize = max(int(pq.size()), maxqsize);
		}
		iterations++;
		if (iterations > MAX_ITERS) {
			cout << "Too many iterations:" << iterations << endl;
			return false;
		}
	}
	cout << "Failed to find match"<<endl;
	return false;
}

int main() {
	string initial = "";
	string goal = "";
	string filepath = "";
	cout << "Input the path to the file" << endl;
	cin >> filepath;


	string line;
	ifstream myfile;
	myfile.open(filepath);
	if (!myfile.is_open()) {
		perror("Error open");
		exit(EXIT_FAILURE);
	}
	int count = 0;
	while (count!=3){
		getline(myfile, line);
		if (line.find('>') < line.length()) { 
			count++;
		}
		else if(count==1){
			initial.append(line);
			initial.push_back(';');
		}
		else if (count == 2) {
			goal.append(line);
			goal.push_back(';');
		}
	}
	goal.pop_back();
	initial.pop_back();
	cout << "initial: " << initial<<endl;
	cout << "Goal: " << goal << endl;
	
	Node* initialState = new Node(initial);
	Node* goalState = new Node(goal);
	
	Astar(initialState,goalState);
	
	

	return 0;
}
