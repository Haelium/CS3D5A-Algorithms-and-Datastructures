// TODO: Exception handling
// TODO: comment each function
// TODO: add header
// TODO: variable names
// TODO: Replace C with nicer C++ functions

#include <stack>
#include <queue>
// remove and replace
#include <cstdio>
#include <cstdlib>
#include <cassert>

using namespace std;

#define NUM_OF_NODES 12

static inline int ascii2index (char n) {
    return (n - 'A');
}

// inverse of ascii2index
static inline char index2ascii (int n) {
    return (n + 'A');
}

class Graph {
public:
    Graph (void);
    void add_link_bi (char vertex_1, char vertex_2, int cost);
    bool depth_first_search (char start_vertex, char end_vertex);
    bool dijkstra_search (char start_vertex, char end_vertex);
private:
    int graph[NUM_OF_NODES][NUM_OF_NODES];
};

inline Graph::Graph (void) {
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

inline void Graph::add_link_bi (char vertex_1, char vertex_2, int cost) {
    // TODO: Exception handling
    graph[ascii2index(vertex_1)][ascii2index(vertex_2)] = cost;
    graph[ascii2index(vertex_2)][ascii2index(vertex_1)] = cost;
}

inline bool Graph::depth_first_search (char start_vertex, char end_vertex) {
    printf("Depth first search\n");
    char current_vertex;
    std::stack<char> unvisited;
    bool visited[NUM_OF_NODES];
    for (int x = 0; x < NUM_OF_NODES; x++) {
        visited[x] = false;
    }
    
    unvisited.push(start_vertex);
    while (!unvisited.empty()) {
        current_vertex = unvisited.top();
        unvisited.pop();    // std::stack::pop does not return top

        printf("%c ", current_vertex);
        if (current_vertex == end_vertex) {
            printf("Vertex found\n");
            return true;
        }
        if (visited[ascii2index(current_vertex)] == false) {
            visited[ascii2index(current_vertex)] = true;
            for (int x = 0; x < NUM_OF_NODES; x++) {
                if (graph[ascii2index(current_vertex)][x] > 0 && visited[x] == false) {
                    unvisited.push(index2ascii(x));
                }
            }
        }
    }
    return false;
}

// Container class, associates a vertex label with a cost from the source in dijktras search
// Used as an element within a priority queue for dijkstras search
class Vertex {
public:
    char vertex;
    int cost_from_source;
};

// Comparison class, used to define how the priority queue in dijkstra's search is ordered
class GreaterCost {
public:
    bool operator ()(Vertex const & vertex_1, Vertex const & vertex_2) {
        return (vertex_1.cost_from_source > vertex_2.cost_from_source);
    }
};

inline bool Graph::dijkstra_search(char start_vertex, char end_vertex) {
    // In this implementeation, start_vertex is the "source"
    char current_v;
    int alt;
    bool optimal_route_found = false;  // default
    // Priority queue, priority is given to Vertex objects whose cost_from_source is lowest
    priority_queue<Vertex, vector<Vertex>, GreaterCost> unvisited;
    int dist_to_vertex[NUM_OF_NODES];       // optimal known distance from source to vertex
    char prev_optimal_vertex[NUM_OF_NODES]; // previous vertex in optimal path from source
    Vertex temp_vertex;

    for (char v = 'A'; v < 'A' + NUM_OF_NODES; v++) {
        dist_to_vertex[ascii2index(v)] = 99999;     // Each vertex begins with infinite cost to source
        prev_optimal_vertex[ascii2index(v)] = 0;    // 0 denotes no route to source from v
    }
    dist_to_vertex[ascii2index(start_vertex)] = 0;
    temp_vertex.vertex = start_vertex;
    temp_vertex.cost_from_source = 0;
    unvisited.push(temp_vertex);

    // While there are nodes which have not been tried, keep looping through the queue
    while (!unvisited.empty()) {
        // remove the first vertex from the queue and calculate the optimal routes to the source (start_vertex) from that vertex
        current_v = unvisited.top().vertex;
        unvisited.pop();

        // If we have reached the target (start_vertex) then a route exists from start_vertex to end_vertex
        if (current_v == end_vertex) {
                optimal_route_found = true;
        }
        // Loop through every neighbour, calculate the cost of taking that route and compare it to the current optimal route
        for (char neighbour_v = 'A'; neighbour_v < 'A' + NUM_OF_NODES; neighbour_v++) {
            if (graph[ascii2index(current_v)][ascii2index(neighbour_v)] >= 0) { // Check that neighbour exists (-1 for no link, 0 for self)
                // alt is the cost of the alternate route
                alt = dist_to_vertex[ascii2index(current_v)] + graph[ascii2index(current_v)][ascii2index(neighbour_v)];
                // If the alternate route is cheaper, this becomes the optimal route from the current vertex (current_v)
                if (alt < dist_to_vertex[ascii2index(neighbour_v)]) {
                    dist_to_vertex[ascii2index(neighbour_v)] = alt;             // Update the cost of optimal route for neighbour_v
                    prev_optimal_vertex[ascii2index(neighbour_v)] = current_v;  // Update the previous node in the optimal route to neighbour_v

                    // push the newly considered neighbour to the queue with its dist_to_vertex
                    temp_vertex.cost_from_source = dist_to_vertex[ascii2index(neighbour_v)];
                    temp_vertex.vertex = neighbour_v;
                    unvisited.push(temp_vertex);
                }
            }
        }
    }

    // Print out the optimal route if it exists
    if (optimal_route_found) {
        char vert = end_vertex; 
        while (vert != start_vertex) {
            printf("%c ", vert);
            vert = prev_optimal_vertex[ascii2index(vert)];
        }
        printf("%c\n", vert);
    }
    // Return the result of the search (true / false)
    return optimal_route_found;
}


int main (void) {
    Graph test_graph;   // declaring a graph object
    // Initialising the graph as illustrated in the assignment handout
    {
        test_graph.add_link_bi('A', 'B', 1);
        test_graph.add_link_bi('B', 'C', 2);
        test_graph.add_link_bi('B', 'D', 2);
        test_graph.add_link_bi('C', 'E', 3);
        test_graph.add_link_bi('C', 'F', 2);
        test_graph.add_link_bi('D', 'G', 2);
        test_graph.add_link_bi('F', 'H', 1);
        test_graph.add_link_bi('F', 'I', 2);
        test_graph.add_link_bi('F', 'J', 4);
        test_graph.add_link_bi('G', 'J', 1);
        test_graph.add_link_bi('G', 'L', 3);
        test_graph.add_link_bi('G', 'K', 2);
        test_graph.add_link_bi('I', 'K', 11);
        test_graph.add_link_bi('J', 'L', 5);
    }
    test_graph.depth_first_search('A', 'I');
    test_graph.dijkstra_search('A', 'I');
    
    return 0;
}