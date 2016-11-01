#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
struct Node {
    char data;
    Node* next;
};

void push_node (Node** list, char data) {
    Node* head = (Node*)malloc(sizeof(Node));
    head->data = data;
    head->next = *list;
    *list = head;
}

// Where memory is already allocated in continuous block
void push_node_c (Node* list, int offset, char data) {
    Node* myNode = (list + sizeof(Node) * offset);
    myNode->data = data;
    myNode->next = myNode + sizeof(Node);
}

void print_list (Node* list) {
    printf("Printing linked list...\n");
    while (list) {
        printf("%c ", list->data);
        list = list->next;
    }
    printf("\n");
}

void delete_list (Node* list) {
    Node* travNode = list;
    Node* killNode = travNode;
    while (travNode->next) {
        travNode = travNode->next;
        free(killNode);
        killNode = travNode;
    }
    free(travNode);
}

void reverse_list (Node** list) {
    int time_n = 0;
    Node* prev = NULL;
    Node* current = *list;
    Node* next;
    while (current) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
        time_n += 4;
    }
    *list = prev;
    printf("Time complexity: T(n) = 4*n + 4 = 4*%d + 4 = %d\n", time_n, time_n + 4);
}

int main (void) {
    Node* myNode = (Node*)malloc(sizeof(Node));
    myNode->next = NULL;
    myNode->data = 'A';
    push_node(&myNode, 'B');
    push_node(&myNode, 'C');
    push_node(&myNode, 'D');

    print_list(myNode);
    reverse_list(&myNode);
    print_list(myNode);

    delete_list(myNode);

    Node* secondlist = (Node*)malloc(sizeof(Node) * 3);
    push_node_c(secondlist, 0, 'A');
    push_node_c(secondlist, 2, 'C');
    push_node_c(secondlist, 1, 'B');

    // Now we can itterate and print like so
    for (int x = 0; x < 3; x++) {
        printf("%c ", (secondlist + x * sizeof(Node))->data);
    }
    printf("\n");
    // Looping through a continuous block of memory is faster because of 
    // prefetching (aka the "L0" cache)

    print_list(secondlist);

    return 0;
}
