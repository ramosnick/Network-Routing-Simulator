#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <string>

struct Edge {

    private: 
    Node* fromNode; 
    Node* toNode;
    double weight;
    bool online;

    public:
    Edge();
    Edge(Node* fromNode, Node* toNode, double weight);

};

struct Node {

    private:
    std::string iPAddress;
    int nodeVal; 
    std::list<Edge> edges;

    public:
    Node();
    Node(int val, std::list<Edge> edges);

};

class Graph {
    
    private:
    int numNodes;
    std::list<Node&> nodeList;

    public:
    Graph();

    int size();
    void printNodes();

    void addNode();
    void removeNode();

};

#endif