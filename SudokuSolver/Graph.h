#ifndef GRAPH_H
#define GRAPH_H
#include <map>
#include <iostream>
#include <utility>
using namespace std;
template <typename T>
class Node{
    private:
        int id;
        T data;
        map<int,Node<T>*> neighbours;
    public:
        void printmap(map<int,Node<T>*> vec){
            for (auto const &pair: vec) {
                std::cout << "{" << pair.first << ": " << pair.second->getData() << "}";
            }
        }
        Node(){
            id=0;
        }
        Node(int idval, T value){
            id = idval;
            data = value;
        }
        void setData(T value){
            data = value;
        }   
        T getData(){
            return data;
        }
        int getWeight(int id){
            return neighbours[id];
        }
        void addNeighbour(Node<T>* neighbour,int weight =0){
            neighbours[neighbour->getId()] = neighbour;
        }
        map<int,int> getneighbours(){
            return neighbours;
        }
        int getId(){
            return id;
        }
        void show(){
            cout << "Node id: "<< this->getId() << ", Data: " << this->getData() <<" neighbours: ";
            printmap(neighbours);
        }
        int* getconnections(){
            int connectedto[neighbours.size()];
            int i =0;
            for (auto const &pair: neighbours) {
                connectedto[i] = pair.first;
                i++;
            }
            return connectedto;
        }
};
template <typename T>
class Graph{
    private:
        int nodes; //will be used for id
        map<int,Node<T>*> allnodes; // id: Node object
    public:
        Graph(){
            nodes = 0;
        }
        bool exists(int id){
            typename map<int,Node<T>*>::iterator it = allnodes.find(id);
            if (it != allnodes.end())
                return true;
            else    
                return false;
        }
        void addNode(int id, T data){
            if(!exists(id)){
                allnodes[id] = new Node<int>(id,data);
                nodes++;
            }else{
                cout<< "Node already in Graph. Please use a different id" <<endl;
            }
        }
        void addNode(Node<T>* node){
            if(!exists(node->getId())){
                allnodes[node->getId()] = node;
                nodes++;
            }else{
                cout<< "Node already in Graph. Please use a different id" <<endl;
            }
            
        }
        void addEdge(int idsrc,int iddes,int weight=0){
            allnodes[idsrc]->addNeighbour(allnodes[iddes],weight);
            allnodes[iddes]->addNeighbour(allnodes[idsrc],weight);
        }
        Node<T>* getNode(int id){
            return allnodes[id];
        }
        bool Neighbours(int idu,int idv){
            return true;
        }
        void DFS();
        void BFS();
        void Djikstra();
        void show(){
            cout << "Graph node count: " << nodes << endl;
            for(auto const &pair: allnodes){
                pair.second->show(); 
                cout<<endl;
            }
        }
        void showEdge(){
            cout << "Edges" <<endl;
        //     for idx in self.allNodes :
        //     node =  self.allNodes[idx]
        //     for con in node.getConnections() : 
        //         print(node.getID(), " --> ", 
        //         self.allNodes[con].getID())
            for(auto const &i: allnodes){
                Node<T>* temp = i.second;
                for(auto &t: temp->getconnections()){
                    cout<< t->getId() << " --->" << allnodes[t]->getID();
                }
            }
         }
};
#endif