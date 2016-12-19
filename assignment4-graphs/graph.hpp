/*
graph.hpp, code implementing a graph using an adjecency matrix encapsulated within a class 
Author: David J. Bourke, Student Number: 12304135
Date started:   2nd of December 2016
Date submitted: 8th of December 2016
Used in: graph.cpp
*/

#include <stack>    // stack (used for depth first search)
#include <queue>    // priority_queue, queue (used for dijkstra_search)

#include <cstdio>   // printf
#include <cassert>  // assert

using namespace std;    // <stack> and <queue> are within namespace std

#define NUM_OF_NODES 12

// hash function which takes a vertex label as input and returns the index of the data in a table
static inline int ascii2index (char n) {
    return (n - 'A');
}

// inverse of ascii2index
static inline char index2ascii (int n) {
    return (n + 'A');
}

// Wrapper class for an undirected graph containing 12 vertices labeled from A to L
// (Class could be modified to work with n vertices by using a dynamic array with some other changes)
class Graph {
public:
    // Default constructor initialises all vertices to be disconnected
    Graph (void);
    // Adds a link from vetex_1 to vertex_2 with a cost
    void add_link (char vertex_1, char vertex_2, int cost);
    // Finds a potentially sub-optimal path from start_vertex to end_vertex using depth-first search in descending alphabetical order
    bool depth_first_search (char start_vertex, char end_vertex);
    // Finds an optimal path from start_vertex to end_vertex using dijkstra's least-cost path algorithm
    bool dijkstra_search (char start_vertex, char end_vertex);
private:
    // Graph is stored in a adjacency matrix
    int graph[NUM_OF_NODES][NUM_OF_NODES];
};

Graph::Graph (void) {
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
}

void Graph::add_link (char vertex_1, char vertex_2, int cost) {
    // Check that vertices are within valid range of values
    assert(vertex_1 >= 'A' && vertex_1 <= 'A' + NUM_OF_NODES);
    assert(vertex_2 >= 'A' && vertex_2 <= 'A' + NUM_OF_NODES);

    graph[ascii2index(vertex_1)][ascii2index(vertex_2)] = cost;
    graph[ascii2index(vertex_2)][ascii2index(vertex_1)] = cost;
}

bool Graph::depth_first_search (char start_vertex, char end_vertex) {
    // Check that inputs are valid
    if (start_vertex < 'A' || start_vertex > 'A' + NUM_OF_NODES || end_vertex < 'A' || end_vertex > 'A' + NUM_OF_NODES) {
        printf("Error: depth_first_search: Invalid input data, valid vertices are between 'A' and 'L'\n");
        return false;
    }

    printf("DFS from '%c' ", start_vertex);
    char current_vertex;
    stack<char> unvisited;  // Stack of unvisited vertices
    // Lookup table accessed using ascii2index, tells us if a vertex has been visited
    bool visited[NUM_OF_NODES];
    // All vertices are initially unvisited
    for (int x = 0; x < NUM_OF_NODES; x++) {
        visited[x] = false;
    }
    
    // Each node is pushed to the stack before it is examined
    unvisited.push(start_vertex);
    while (!unvisited.empty()) {
        // Top of stack is examined first as it is removed from the stack
        current_vertex = unvisited.top();
        unvisited.pop();

        printf("%c ", current_vertex);
        if (current_vertex == end_vertex) { // Exit early if end_vertex is found
            printf("target found - HALT\n");
            return true;
        }
        // If current_vertex was not visited before, add unvisited neighbours to the stack
        if (visited[ascii2index(current_vertex)] == false) {
            visited[ascii2index(current_vertex)] = true;
            for (int x = 0; x < NUM_OF_NODES; x++) {
                if (graph[ascii2index(current_vertex)][x] > 0 && visited[x] == false) {
                    unvisited.push(index2ascii(x));
                }
            }
        }
    }
    // If all vertices have been visited without finding the end_vertex, return false
    printf("target not found - HALT\n");
    return false;
}

// Container class, associates a vertex label with a cost from the source in dijktras search
// Used as an element within a priority queue for dijkstras search
class VertexQueueNode {
public:
    char vertex;
    int cost_from_source;
};

// Comparison class, used to define how the priority queue in dijkstra's search is ordered
class GreaterCost {
public:
    bool operator ()(VertexQueueNode const & vertex_1, VertexQueueNode const & vertex_2) {
        return (vertex_1.cost_from_source > vertex_2.cost_from_source);
    }
};

bool Graph::dijkstra_search(char start_vertex, char end_vertex) {
    // Check that inputs are valid
    if (start_vertex < 'A' || start_vertex > 'A' + NUM_OF_NODES || end_vertex < 'A' || end_vertex > 'A' + NUM_OF_NODES) {
        printf("Error: dijkstra_search: Invalid input data, valid vertices are between 'A' and 'L'\n");
        return false;
    }

    bool optimal_route_found = false;  // default return value
    // In this implementeation, start_vertex is the "source"
    char current_v;     // Stores the vertex whose best cost from source is being calculated
    int alt_route_cost; // Stores result of alternative routes to current_v before they are made permenant
    // vertex_queue_node used as temporary tuple containing a vertex label and the optimal known cost from source
    VertexQueueNode vertex_queue_node;
    // Priority queue, priority is given to Vertex objects whose cost_from_source is lowest
    // Consult STL doccumentation for the <queue> header to understand the declaration
    priority_queue<VertexQueueNode, vector<VertexQueueNode>, GreaterCost> unvisited;
    // Simple hashtables accessed with the ascii2index functin
    int dist_to_vertex[NUM_OF_NODES];       // optimal known distance from source to vertex
    char prev_optimal_vertex[NUM_OF_NODES]; // previous vertex in optimal path from source to vertex

    // Inititalise dist_to_vertex and prev_optimal_vertex tables
    for (char v = 'A'; v < 'A' + NUM_OF_NODES; v++) {
        dist_to_vertex[ascii2index(v)] = 99999;     // Each vertex begins with infinite cost from source
        prev_optimal_vertex[ascii2index(v)] = 0;    // 0 denotes no route to source from v
    }

    dist_to_vertex[ascii2index(start_vertex)] = 0;  // Distance from vertex to itself is 0
    // Enqueue the source node first
    vertex_queue_node.vertex = start_vertex;
    vertex_queue_node.cost_from_source = 0;
    unvisited.push(vertex_queue_node);

    // While there are nodes which have not been tried, keep looping through the queue
    while (!unvisited.empty()) {
        // remove the first vertex from the queue and calculate the optimal routes to the source (start_vertex) from that vertex
        current_v = unvisited.top().vertex;
        unvisited.pop();

        // If we have reached the target (start_vertex) then a route exists from start_vertex to end_vertex
        if (current_v == end_vertex) {
                optimal_route_found = true;
        }

        // Loop through every neighbour, calculate the cost of taking that route and compare it to the current known optimal route
        for (char neighbour_v = 'A'; neighbour_v < 'A' + NUM_OF_NODES; neighbour_v++) {
            if (graph[ascii2index(current_v)][ascii2index(neighbour_v)] >= 0) { // Check that neighbour exists (-1 for no link, 0 for self)
                // alternate route cost = cost to current_vertex + link from current vertex to neighbour (alt = dist(u) + cost(u, v))
                alt_route_cost = dist_to_vertex[ascii2index(current_v)] + graph[ascii2index(current_v)][ascii2index(neighbour_v)];
                // If the alternate route is cheaper, this becomes the optimal route from the current vertex (current_v)
                if (alt_route_cost < dist_to_vertex[ascii2index(neighbour_v)]) {
                    dist_to_vertex[ascii2index(neighbour_v)] = alt_route_cost;  // Update the cost of optimal route for neighbour_v
                    prev_optimal_vertex[ascii2index(neighbour_v)] = current_v;  // Update the previous node in the optimal route to neighbour_v

                    // push the newly considered neighbour to the queue with its dist_to_vertex
                    vertex_queue_node.cost_from_source = dist_to_vertex[ascii2index(neighbour_v)];
                    vertex_queue_node.vertex = neighbour_v;
                    unvisited.push(vertex_queue_node);
                }
            }   // endif (neighbour exists)
        }   // endfor (loop through every neighbour of current_v)

    }   // endwhile (priority queue not empty)
    // Dijkstras algorithm has been calculated when the previous loop ends (if a route exists)

    // This section just prints the route (if a route exists) and returns a bool to state if a route is found (true / false)
    printf("Dijkstra path from `%c' length %d\n", start_vertex, dist_to_vertex[ascii2index(start_vertex)]);
    
    // Since dijkstra's search is calculated by storing the best parent, we use a stack to print in start -> end order
    stack<char> route;

    if (optimal_route_found) {  // Print out the optimal route if it exists
        char vert = end_vertex; 
        while (vert != start_vertex) {
            route.push(vert);
            vert = prev_optimal_vertex[ascii2index(vert)];
        }
        
        while (!route.empty()) {
            vert = route.top();
            route.pop();
            printf("%c length %d, parent %c\n", vert, dist_to_vertex[ascii2index(vert)], prev_optimal_vertex[ascii2index(vert)]);
        }
        printf("target found - HALT\n");
    } else {
        printf("target not found - HALT\n");
    }

    // Return the result of the search (true / false)
    return optimal_route_found;
}
