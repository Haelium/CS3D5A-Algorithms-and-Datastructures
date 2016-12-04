#include "graph.h"

int main (void) {
    initialise_graph();
    connect_bi('A', 'B', 1);

    breadth_first_search('A', 'B');
    breadth_first_search('A', 'Z');
    return 0;
}