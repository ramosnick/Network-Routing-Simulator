#include "Graph.h"
#include <iostream>
#include <format>
#include <algorithm>

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
    edges.emplace_back(toIP, weight); //Emplace creates an Edge object for me with given parameters
}

std::vector<Edge>& Node::getEdges() {
        return edges;
    }

std::ostream& operator<<(std::ostream& os, const Node& node) {
    os << "IP Address: " << node.iPAddress << std::endl;
    os << "Connected to:\n" << std::endl;
    for(int i; i < size(node.edges) ; i++) {
        os << node.edges[i] << std::endl;
    }
}

/*-----------Edge Methods:----------*/

Edge::Edge() {
    toIP =""; 
    weight = 0; 
    online = false;
};

Edge::Edge(std::string toIP, double weight) {
    this->toIP = toIP;
    this->weight = weight;
    online = true;
};

std::string Edge::getToIP() {
    return this->toIP;
}

std::ostream& operator<<(std::ostream& os, const Edge& edge) {
    os << "IP: " << edge.toIP << std::endl;
    os << "Latency (weight): " << edge.weight << std::endl;
}

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
    std::cout << "Edge added\nFrom IP: " << fromIP << std::endl;
    std::cout << "To IP: " << toIP << std::endl;
    return;
}

void Graph::removeEdge(std::string fromIP, std::string toIP, double weight) {



}

//Remove node or edge
void Graph::removeNode(std::string iPAddress) {
    if(nodeMap.count(iPAddress) == 0) {
        std::cout << "Node not found..." << std::endl;
        return;
    }
    //FIXME: Need to visit connecting Nodes and delete Edges leading to this Node before deleting the Node...
    /*Copied from Gemini: Don't want to implement exactly like this,
    just using it as an example 
    
    // Inside your loop, targeting the neighbor's vector:
neighborNode->edges.erase(
    std::remove_if(neighborNode->edges.begin(), neighborNode->edges.end(),
        [&deletedIP](const Edge& e) {
            return e.targetIP == deletedIP;
        }),
    neighborNode->edges.end()
);*/
    for(auto& edge : nodeMap[iPAddress]->getEdges()) {

        if(edge.getToIP() == iPAddress) {
            nodeMap[iPAddress]->getEdges().erase(edge);
        }

    }

    delete nodeMap[iPAddress];    
    nodeMap.erase(iPAddress);
    this->numNodes--;
}

