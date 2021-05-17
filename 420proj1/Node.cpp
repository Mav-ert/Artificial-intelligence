#include "State.h"
#include "Node.h"

using namespace std;
// checks whether this state matches another (like the goal)
bool Node::goal_test(State* goal) {
	return nodestate->match(goal);
}


// gets the successors of the state, and wraps them in Nodes
vector<Node*> Node::successors(){
	vector<State*> statesuccessors = nodestate->successors();
	vector<Node*> ret;
	for (int i = 0;i < statesuccessors.size();i++) {
		ret.push_back(new Node(statesuccessors[i]));
		ret[i]->setParent(this);
	}
	return ret;
}


string Node::hash() {
	return nodestate->hash();
} // return hash key of state


void Node::print_path() {
	Node* curr = this;
	vector<State*> queue;
	int n = this->getDepth();
	while (n >= 0) {
		queue.push_back(curr->nodestate);
		curr = curr->parent;
		n--;
	}
	for(int i = queue.size()-1;i >=0;i--) {
		cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl<<"move "<< queue.size()-i-1 <<endl;
		queue[i]->print();
	}
	cout << "End of path" << endl;
} // print sequence of states from root down to this

Node* Node::add(State* state) {
		Node* a = new Node(state);
		return a;
}
void Node::setParent(Node* Parent) {
  parent = Parent;
  depth = Parent->getDepth() + 1;
}

State* Node::getState() {
		return nodestate;
	}