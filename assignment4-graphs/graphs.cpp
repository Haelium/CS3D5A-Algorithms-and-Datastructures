// TODO: Exception handling
// TODO: comment each function
// TODO: add header
// TODO: variable names
// TODO: Replace C with nicer C++ functions

#include <stack>
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

inline bool Graph::dijkstra_search(char start_vertex, char end_vertex) {
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
    return 0;
}