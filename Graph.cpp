#include "Graph.h"
#include <iostream>

/*-----------Node Methods:----------*/
Node::Node() {
    this->nodeVal = 0;
    online = false;
}

Node::Node(int val) {
    this->nodeVal = val;
    online = true;
}

Node::Node(int val, std::string iPAddress) {
    this->nodeVal = val;
    this->iPAddress = iPAddress;
    online = true;
}

void Node::addEdge(std::string toIP, double weight) {
    edges.emplace_back(toIP, weight);
}

/*-----------Edge Methods:----------*/

Edge::Edge() {toIP =""; weight = 0; online = false;};

Edge::Edge(std::string toIP, double weight) {
    this->toIP = toIP;
    this->weight = weight;
    online = true;
};

/*-----------Graph Methods:----------*/
Graph::Graph() {
    numNodes = 0;
};

//Add node or edge
void Graph::addNode(int nodeVal, std::string iPAddress) {
    Node* newNode = new Node(nodeVal, iPAddress);
    nodeMap[iPAddress] = newNode;
    numNodes++;
    return;
}

void Graph::addEdge(std::string fromIP, std::string toIP, double weight) {
    nodeMap[fromIP]->addEdge(toIP, weight);
}

void Graph::removeEdge(std::string fromIP, std::string toIP, double weight) {



}

//Remove node or edge
void Graph::removeNode(std::string iPAddress) {
    if(nodeMap[iPAddress] == 0) {
        std::cout << "Node not found..." << std::endl;
        return;
    }
}

