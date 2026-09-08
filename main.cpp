#include "Graph.h"
#include <iostream>

int main() {

    Graph testGraph = Graph();
    
    std::cout << "\nTest 1" << std::endl;

    testGraph.addNode(0, "0");
    testGraph.addNode(1, "1");
    testGraph.addEdge("0", "1", 3);
    testGraph.addEdge("1", "0", 5);
    testGraph.printGraph();

    std::cout << "Test 2" << std::endl;

    testGraph.removeEdge("0", "1");
    testGraph.printGraph();

    std::cout << "\nTest 3" << std::endl;

    testGraph.updateEdge("1", "0", 99);
    testGraph.printGraph();
    
    
};