#include <stdlib.h>
#include <stdbool.h>

typedef struct Node Node;
struct Node {
    Node* ahead; // Served before this node
    Node* behind; // Served after this node
    char data;
};

typedef struct Char_Queue Char_Queue;
struct Char_Queue {
    Node* first;
    Node* last;
};

Char_Queue* initialise_queue (void) {
    Char_Queue* queue_ptr = (Char_Queue*)malloc(sizeof(Char_Queue));
    queue_ptr->first = NULL;
    queue_ptr->last = NULL;

    return queue_ptr;
}

bool empty_queue (Char_Queue* char_queue_ptr) {
    if (char_queue_ptr->first == NULL) {
        return true;
    } else {
        return false;
    }
}

// Creates a new node and appends it to the end (last) of the queue
void enqueue (Char_Queue* queue_ptr, char data) {
    Node* new_node_ptr = (Node*)malloc(sizeof(Node));
    new_node_ptr->data = data;
    if (empty_queue(queue_ptr)) {
        queue_ptr->first = new_node_ptr;
        queue_ptr->last = new_node_ptr;
        new_node_ptr->ahead = NULL;
        new_node_ptr->behind = NULL;
    } else {
        new_node_ptr->ahead = queue_ptr->last;
        new_node_ptr->behind = NULL;
        queue_ptr->last->behind = new_node_ptr;
        queue_ptr->last = new_node_ptr;
    }
}

// Removes the first node in the queue and returns the data stored in that node (not the node itself)
char dequeue (Char_Queue* queue_ptr) {
    assert (queue_ptr->first != NULL); // Can't dequeue an element from an empty queue

    Node* temp_node_ptr = queue_ptr->first;       // Record the current head of queue
    char data = temp_node_ptr->data;    // Record the data to be returned

    // Promote the 2nd node in the queue to the head of the queue
    queue_ptr->first = queue_ptr->first->behind;
    if (queue_ptr->first != NULL) {
        queue_ptr->first->ahead = NULL;
    } else {
        queue_ptr->last = NULL;
    }

    free(temp_node_ptr);    // Free the memory of the dequeued node    

    return data;
}