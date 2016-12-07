#include <stack>
#include <map>
#include <vector>
#include <set>

/* The graph is illustrated below

      E     H
      |    /
      C - F - I - -\
     /     \        \
A - B       J        |
     \     / \       |
      D - G - L      |
           \        /
            K - - -/
*/

static const int disconnected = -1;

using namespace std;

class Graph {
public:
    Graph(char* node_list, int num_of_nodes);
    ~Graph (void);
    // void add_vertex (char);
    void add_edge (char, char);
    bool breadth_first_search (char, char);
    bool dijkstra_search (char, char);
private:
    int number_of_nodes;
    int* graph_matrix; // declared on heap so Graph can be resized if necessary
};

Graph::Graph (char* node_list, int num_of_nodes) {
    number_of_nodes = num_of_nodes;
    graph_matrix = (int*)malloc(sizeof(int) * number_of_nodes * number_of_nodes);

    // label all possible combinations of nodes as being disconnected
    for (int x = 0; x < number_of_nodes * number_of_nodes; x += sizeof(int)) {
        (graph_matrix + x) = disconnected;
    }
}

void Graph::add_edge (char v1, char v2, int cost) {
    // check that v1 and v2 exist
}

Graph::~Graph (void) {
    // delete all vertex structs here
}