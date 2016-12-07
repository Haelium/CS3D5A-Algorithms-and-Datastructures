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
    int get_link_cost (char n1, char n2);
    bool depth_first_search (char start_vertex, char end_vertex);
    bool dijkstra_search (char start_vertex, char end_vertex);
    void print(void) {
        for (int x = 0; x < NUM_OF_NODES; x++) {
            for (int y = 0; y < NUM_OF_NODES; y++) {
                printf("%d ", graph[x][y]);
            }
        }
    }
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

inline int Graph::get_link_cost (char n1, char n2) {
    // check if n1 or n2 are out of range (ascii values from 'A' to 'G')
    assert(n1 >= 'A' && n1 <= 'L');
    assert(n2 >= 'A' && n2 <= 'L');

    // return result from graph matrix
    return graph[ascii2index(n1)][ascii2index(n2)];
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

class Vertex {
public:
    char vertex;
    int cost_from_source;
};

class GreaterCost {
public:
    bool operator ()(Vertex const & vertex_1, Vertex const & vertex_2) {
        return (vertex_1.cost_from_source > vertex_2.cost_from_source);
    }
};

inline bool Graph::dijkstra_search(char start_vertex, char end_vertex) {
    char current_v;
    int alt;
    // Todo: explain what's going on here with this C++ STL jibberish'
    priority_queue<Vertex, vector<Vertex>, GreaterCost> unvisited;
    int dist_to_vertex[NUM_OF_NODES];       // distance from source to vertex
    char prev_optimal_vertex[NUM_OF_NODES]; // previous vertex in optimal path from source
    Vertex current_vertex;

    for (char v = 'A'; v < 'A' + NUM_OF_NODES; v++) {
        if (v != start_vertex) {    // don't add source vertex here
            dist_to_vertex[ascii2index(v)] = 99999;
            prev_optimal_vertex[ascii2index(v)] = 0;
            current_vertex.vertex = v;
            current_vertex.cost_from_source = 99999;
            //unvisited.push(current_vertex);
        }
    }/*
 5      for each vertex v in Graph:             // Initialization
 6          dist[v] ← INFINITY                  // Unknown distance from source to v
 7          prev[v] ← UNDEFINED                 // Previous node in optimal path from source
 8          add v to Q                          // All nodes initially in Q (unvisited nodes)
 9
10      dist[source] ← 0                        // Distance from source to source
11      */
    dist_to_vertex[ascii2index(start_vertex)] = 0;
    current_vertex.vertex = start_vertex;
    current_vertex.cost_from_source = 0;
    unvisited.push(current_vertex);
//      while Q is not empty:
    while (!unvisited.empty()) {
        //printf("LOL");
//13          u ← vertex in Q with min dist[u]    // Source node will be selected first
//14          remove u from Q 
        current_v = unvisited.top().vertex;
        unvisited.pop();
        //printf("%c ", current_v);
//15          
//16          for each neighbor v of u:           // where v is still in Q.
        for (char neighbour_v = 'A'; neighbour_v < 'A' + NUM_OF_NODES; neighbour_v++) {
//17              alt ← dist[u] + length(u, v)
            if (graph[ascii2index(current_v)][ascii2index(neighbour_v)] >= 0) {
                alt = dist_to_vertex[ascii2index(current_v)] + graph[ascii2index(current_v)][ascii2index(neighbour_v)];
//18              if alt < dist[v]:               // A shorter path to v has been found
//19                  dist[v] ← alt 
//20                  prev[v] ← u 
                if (alt < dist_to_vertex[ascii2index(neighbour_v)]) {
                    dist_to_vertex[ascii2index(neighbour_v)] = alt;
                    prev_optimal_vertex[ascii2index(neighbour_v)] = current_v;

                    current_vertex.cost_from_source = dist_to_vertex[ascii2index(neighbour_v)];
                    current_vertex.vertex = neighbour_v;
                    unvisited.push(current_vertex);
                }
            }
        }
//21
    }
//22      return dist[], prev[]

    char vert = end_vertex; 
    while (vert != start_vertex) {
        printf("%c ", vert);
        vert = prev_optimal_vertex[ascii2index(vert)];
    }
    printf("%c\n", vert);

    return false;
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