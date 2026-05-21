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
    Edge(); //Done
    Edge(std::string toIP, double weight); //Done

    std::string getToIP(); //Done

    friend std::ostream& operator<<(std::ostream& os, const Edge& edge); //Needs testing

};

class Node {

    private:
    std::string iPAddress;
    int nodeVal; 
    std::vector<Edge> edges;
    bool online;

    public:
    Node(); //Needs testing
    Node(int val); //Needs testing
    Node(int val, std::string iPAddress); //Needs testing

    void addEdge(std::string toIP, double weight); //Needs testing
    void removeEdge(std::string toIP); //Not started

    std::vector<Edge>& getEdges(); //Needs testing

    friend std::ostream& operator<<(std::ostream& os, const Node& node); //Needs testing

};

class Graph {
    
    private:
    int numNodes;
    std::unordered_map<std::string, Node*> nodeMap;

    public:
    Graph(); //Done?

    int size(); //Not started
    void printNodes(); //Not started

    void addNode(int nodeVal, std::string iPAddress); //Needs testing
    void removeNode(std::string iPAddress); //Work in Progress

    void addEdge(std::string fromIP, std::string toIP, double weight); //Needs testing
    void removeEdge(std::string fromIP, std::string toIP, double weight); //Not started

};

#endif