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

    std::string getToIP() const; //Done
    void updateWeight(double newWeight); //Done

    friend std::ostream& operator<<(std::ostream& os, const Edge& edge); //Needs testing

};

class LSA {

    private:
    int seqNum;
    std::string fromIp;
    std::vector<Edge> neighbors;

    public:
    //Constructors
    LSA();
    LSA(std::string fromIp);
    LSA(int seqNum, std::string fromIp, std::vector<Edge> neighbors);

    //Getters
    int getSeqNum();
    std::string getFromIp();
    const std::vector<Edge>& getNeighbors();
    
    //Setters
    void setSeqNumber(int seqNum);
    void setFromIp(std::string fromIp);
    void addNeighbor(Edge neighbor);

};

class Node {

    private:
    std::string iPAddress;
    int nodeVal; 
    std::vector<Edge> edges;
    std::unordered_map<std::string, std::string> routingTable;
    bool online;

    public:
    Node(); //Needs testing
    Node(int val); //Needs testing
    Node(int val, std::string iPAddress); //FUNCTIONAL

    std::string getIP() const; //FUNCTIONAL

    void addEdge(std::string toIP, double weight); //FUNCTIONAL
    void removeEdge(std::string toIP); //FUNCTIONAL (Could refactor for loop to do away with indexing)

    std::vector<Edge>& getEdges(); //FUNCTIONAL

    friend std::ostream& operator<<(std::ostream& os, const Node& node); //Needs testing

    void updateRoutingTable();

};

class Graph {
    
    private:
    int numNodes;
    std::unordered_map<std::string, Node*> nodeMap;

    public:
    Graph(); //FUNCTIONAL

    ~Graph(); //Destructor

    int size(); //Not started
    void printGraph(); //FUNCTIONAL

    void addNode(int nodeVal, std::string iPAddress); //FUNCTIONAL
    void removeNode(std::string iPAddress); //FUNCTIONAL

    void addEdge(std::string fromIP, std::string toIP, double weight); //FUNCTIONAL
    void removeEdge(std::string fromIP, std::string toIP); //FUNCTIONAL

    void updateEdge(std::string fromIP, std::string toIP, double newWeight); //Work in progress

    //THE FUN STUFF >:)

    void updateRoutingTable(); //Work in progress

};

#endif