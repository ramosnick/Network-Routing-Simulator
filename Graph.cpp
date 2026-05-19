#include "Graph.h"

Node::Node() {
    this->nodeVal = NULL;
}

Node::Node(int val, std::list<Edge> edges) {
    this->nodeVal = val;
    
}

Edge::Edge() {fromNode = nullptr; toNode =nullptr; };

Edge::Edge(Node* fromNode, Node* toNode) {
    this->fromNode = fromNode;
    this->toNode = toNode;
};

