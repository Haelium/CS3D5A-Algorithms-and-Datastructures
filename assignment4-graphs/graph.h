#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#include "queue.h"

#define NUM_OF_NODES 12

// Make this graph static since it should only be accessed using the wrapper functions
static int graph[NUM_OF_NODES][NUM_OF_NODES];

// table indicating whether a node has been visited (used in breadth first search and dijkstra search)
//static bool visited[NUM_OF_NODES];

// hashes the character to an index I where (0 <= I < NUM_OF_NODES)
// used to access the graph matrix which stores the edges and the "visited" look up table
static inline int ascii2index (char n) {
    return (n - 'A');
}

// inverse of ascii2index
static inline char index2ascii (int n) {
    return (n + 'A');
}

void initialise_graph (void) {
    // set all edge costs to -1, denoting that no edge exists
    for (int x = 0; x < NUM_OF_NODES; x++) {
        for (int y = 0; y < NUM_OF_NODES; y++) {
            graph[x][y] = -1;
        }
    }

    // Set cost of node_n -> node_n to 0 for all n
    for (int n = 0; n < NUM_OF_NODES; n++) {
        graph[n][n] = 0;
    }

    // Set all nodes as "unvisited"
    //for (int x = 0; x < NUM_OF_NODES; x++) {
    //    visited[x] = false;
    //}
}

// create a bidirectional link between nodes n1 and n2
void connect_bi (char n1, char n2, int cost) {
    // check if n1 or n2 are out of range (ascii values from 'A' to 'G')
    assert(n1 >= 'A' && n1 <= 'L');
    assert(n2 >= 'A' && n2 <= 'L');

    // connect n1 -> n2 and n2 -> n1 with the same cost for each direction
    // ascii2index function converts ascii character to index for the graph matrix
    graph[ascii2index(n1)][ascii2index(n2)] = cost;
    graph[ascii2index(n2)][ascii2index(n1)] = cost;
}

int get_link_cost (char n1, char n2) {
    // check if n1 or n2 are out of range (ascii values from 'A' to 'G')
    assert(n1 >= 'A' && n1 <= 'L');
    assert(n2 >= 'A' && n2 <= 'L');

    // return result from graph matrix
    return graph[ascii2index(n1)][ascii2index(n2)];
}

bool breadth_first_search (char start_vertex, char end_vertex) {
    printf("Breadth first search\n");
    char current_vertex;
    Char_Queue* unvisited = initialise_queue();
    bool visited[NUM_OF_NODES];
    for (int x = 0; x < NUM_OF_NODES; x++) {
        visited[x] = false;
    }
    enqueue(unvisited, start_vertex);

    while (!empty_queue(unvisited)) {
        current_vertex = dequeue(unvisited);
        visited[ascii2index(current_vertex)] = true;
        printf("%c - ", current_vertex);
        if (current_vertex == end_vertex) {
            printf("Node found\n");
            return true;
        }
        for (int x = 0; x < NUM_OF_NODES; x++) {
            if (graph[ascii2index(current_vertex)][x] > 0 && visited[x] == false) {
                enqueue(unvisited, index2ascii(x));
            }
        }
    }
    printf("Node not found\n");
    return false;
}