#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <unordered_map>

class Node;

class Edge {

    private: 
    std::string toIP;
    double weight;
    bool online;

    public:
    Edge();
    Edge(std::string toIP, double weight);

};

class Node {

    private:
    std::string iPAddress;
    int nodeVal; 
    std::vector<Edge> edges;
    bool online;

    public:
    Node();
    Node(int val);
    Node(int val, std::string iPAddress);

    void addEdge(std::string toIP, double weight);
    void removeEdge(std::string toIP);

};

class Graph {
    
    private:
    int numNodes;
    std::unordered_map<std::string, Node*> nodeMap;

    public:
    Graph();

    int size();
    void printNodes();

    void addNode(int nodeVal, std::string iPAddress);
    void removeNode(std::string iPAddress);

    void addEdge(std::string fromIP, std::string toIP, double weight);
    void removeEdge(std::string fromIP, std::string toIP, double weight);

};

#endif