#include "Graph.h"
#include <iostream>
using namespace std;

int main(){
    Graph<int> g = Graph<int>();
    g.addNode(1,4);
    g.addNode(2,3);
    g.addEdge(1,2);
    g.show();
    g.showEdge();
    cout<< g.getNode(1)->getData() <<endl;
}