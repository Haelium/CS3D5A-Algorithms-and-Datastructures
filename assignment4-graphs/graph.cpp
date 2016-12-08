/*
graph.cpp, code showing the use of a graph with search functions
Author: David J. Bourke, Student Number: 12304135
Date started:   2nd of December 2016
Date submitted: 8th of December 2016
Depends on: graph.hpp
*/

#include "graph.hpp"

int main (void) {
    Graph test_graph;   // declaring a graph object
    // Initialising the graph as illustrated in the assignment handout
    {
        test_graph.add_link('A', 'B', 1);
        test_graph.add_link('B', 'C', 2);
        test_graph.add_link('B', 'D', 2);
        test_graph.add_link('C', 'E', 3);
        test_graph.add_link('C', 'F', 2);
        test_graph.add_link('D', 'G', 2);
        test_graph.add_link('F', 'H', 1);
        test_graph.add_link('F', 'I', 2);
        test_graph.add_link('F', 'J', 4);
        test_graph.add_link('G', 'J', 1);
        test_graph.add_link('G', 'L', 3);
        test_graph.add_link('G', 'K', 2);
        test_graph.add_link('I', 'K', 11);
        test_graph.add_link('J', 'L', 5);
    }
    // Test data as described in assignment handout
    test_graph.depth_first_search('A', 'X');
    test_graph.depth_first_search('K', 'B');
    test_graph.dijkstra_search('A', 'X');
    test_graph.dijkstra_search('A', 'J');
    
    return 0;
}