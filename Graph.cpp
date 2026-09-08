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

std::string Node::getIP() const {
    return this->iPAddress;
}

Graph& Node::getLocalGraph() {
    return localGraph;
}

void Node::addEdge(std::string toIP, double weight) {

    edges.emplace_back(toIP, weight); //Emplace creates an Edge object for me with given parameters

}

void Node::removeEdge(std::string toIP) {

    for(int i = 0; i < edges.size(); i++) {
        if(edges[i].getToIP() == toIP) {
            std::cout << "Deleted Edge:\n" << edges[i] << std::endl;
            edges.erase(edges.begin() + i);
            return;
        }
    }
    std::cout << "No IPs matching " << toIP << "found..." << std::endl;
    return;

}

std::vector<Edge>& Node::getEdges() {
        return edges;
    }

void Node::updateEdges(std::vector<Edge> newEdges) {

    this->edges = newEdges; //Turns edges into a copy of newEdges

}

std::ostream& operator<<(std::ostream& os, const Node& node) {
    os << "IP Address: " << node.iPAddress << std::endl;
    os << "Connected to:\n" << std::endl;
    for(int i = 0; i < size(node.edges) ; i++) {
        os << node.edges[i] << std::endl;
    }
    return os;
}

void Node::newLSA() {
    LSA(this->currentSeqNum, this->iPAddress, edges);

}

void Node::receiveLSA(LSA lsa) {
    //If newer LSA not received from this IP
    if(lsa.getSeqNum() > sequenceTable[lsa.getFromIp()]) {
        //FIXME: Update localMap with new data from LSA
        getLocalGraph().getNodeMap()[lsa.getFromIp()]->updateEdges(lsa.getNeighbors());
        //Don't forget to update sequence number table when new nodes are added.
    } else {
        return; //LSA is stale, exit fxn call.
    }

}

void Node::updateRoutingTable() {

    //Dijkstras implementation...

}

/*-----------Edge Methods:----------*/

Edge::Edge() {
    toIP =""; 
    weight = 0; 
    online = false;
}

Edge::Edge(std::string toIP, double weight) {
    this->toIP = toIP;
    this->weight = weight;
    online = true;
}

std::string Edge::getToIP() const {
    return this->toIP;
}

void Edge::updateWeight(double newWeight) {

    this->weight = newWeight;

}

std::ostream& operator<<(std::ostream& os, const Edge& edge) {
    os << "IP: " << edge.toIP << std::endl;
    os << "Latency (weight): " << edge.weight << std::endl;
    return os;
}

/*------------LSA Methods:-----------*/

LSA::LSA() {

    this->seqNum = 0;
    this->fromIp = "";

}

LSA::LSA(std::string fromIp) {
    
    this->seqNum = 0;
    this->fromIp = fromIp;

}

LSA::LSA(int seqNum, std::string fromIp, std::vector<Edge> neighbors) {

        this->seqNum = seqNum;
        this->fromIp = fromIp;
        this->neighbors = neighbors;
}

int LSA::getSeqNum() {

    return this->seqNum;

}

std::string LSA::getFromIp() {

    return this->fromIp;

}

const std::vector<Edge>& LSA::getNeighbors() {

    return this->neighbors;

}

void LSA::setSeqNumber(int seqNum) {

    this->seqNum = seqNum;

}

void LSA::setFromIp(std::string fromIp) {

    this->fromIp = fromIp;

}

void LSA::addNeighbor(Edge neighbor) {

    this->neighbors.push_back(neighbor);

}

/*-----------Graph Methods:----------*/
Graph::Graph() {
    numNodes = 0;
}

Graph::~Graph() {
    for(auto& [iP, node] : nodeMap) {
        if(node) {
            delete node;
        }
    }
}

void Graph::printGraph() {
    std::cout << "Nodes currently in graph:\n" << std::endl;
    for(const auto& [nodeVal, nodePointer] : nodeMap) {
        std::cout << "Node: " << nodeVal << " IP: " << nodePointer->getIP() << std::endl;
        
        if(nodePointer->getEdges().size() > 0) {
            std::cout << "Connects to : " << std::endl;
        }

        for(const auto& edge : nodePointer->getEdges()) {
            std::cout << edge << std::endl;
        }
    }
}
//Add node or edge
void Graph::addNode(int nodeVal, std::string iPAddress) {
    Node* newNode = new Node(nodeVal, iPAddress);
    nodeMap[iPAddress] = newNode;
    numNodes++;
    return;
}

void Graph::addEdge(std::string fromIP, std::string toIP, double weight) {
    //Guard clause to prevent the creation of a new Node in the below for loop...
    if(nodeMap.count(fromIP) == 0 || nodeMap.count(toIP) == 0) {
        std::cout << "Edge creation failed, one or more Nodes doesn't exist..." << std::endl;
        return;
    }
    
    //Guard clause to prevent the creation of duplicate Edges
    for(const auto& edge : nodeMap[fromIP]->getEdges()) {
        if(edge.getToIP() == toIP) {
            std::cout << "Edge already exists, try updateEdge()\n" << std::endl;
            return;
        }
    }
    
    nodeMap[fromIP]->addEdge(toIP, weight);
    std::cout << "Edge added\nFrom IP: " << fromIP << std::endl;
    std::cout << "To IP: " << toIP << std::endl;
    return;
}

//Remove node or edge
void Graph::removeNode(std::string iPAddress) {
    if(nodeMap.count(iPAddress) == 0) {
        std::cout << "Node not found..." << std::endl;
        return;
    }
    
    for(auto& edge : nodeMap[iPAddress]->getEdges()) {

        Node* neighborNode = nodeMap[edge.getToIP()];
        neighborNode->getEdges().erase(std::remove_if(neighborNode->getEdges().begin(), neighborNode->getEdges().end(), [&iPAddress](Edge& e) {return e.getToIP() == iPAddress;}), neighborNode->getEdges().end());

    }

    delete nodeMap[iPAddress];    
    nodeMap.erase(iPAddress);
    this->numNodes--;
}

std::unordered_map<std::string, Node*>& Graph::getNodeMap() {

    return nodeMap;

}

void Graph::removeEdge(std::string fromIP, std::string toIP) {

    nodeMap[fromIP]->removeEdge(toIP);
}

void Graph::updateEdge(std::string fromIP, std::string toIP, double newWeight) {
    if(nodeMap.count(fromIP) == 0 || nodeMap.count(toIP) == 0) {
        std::cout << "Failed to update Edge, one or more Nodes don't exist" << std::endl;
        return;
    }
    for(auto& edge : nodeMap[fromIP]->getEdges()) {
        if(edge.getToIP() == toIP) {
            edge.updateWeight(newWeight);
            return;
        }
    }
    std::cout << "Edge not found, nothing updated" << std::endl;
}