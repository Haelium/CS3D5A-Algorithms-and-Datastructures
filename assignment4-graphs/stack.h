#include <stdlib.h>
#include <stdbool.h>

typedef struct Stack_Node Stack_Node;
struct Stack_Node {
    Stack_Node* down;
    char data;
};

typedef struct Char_Stack Char_Stack;
struct Char_Stack {
    Stack_Node* top;
};

Char_Stack* initialise_stack (void) {
    Char_Stack* stack_ptr = (Char_Stack*)malloc(sizeof(Char_Stack));
    stack_ptr->top = NULL;

    return stack_ptr;
}

bool empty_stack (Char_Stack* char_stack_ptr) {
    if (char_stack_ptr->top == NULL) {
        return true;
    } else {
        return false;
    }
}

// Creates a new node and pushes it to the top
void push (Char_Stack* stack_ptr, char data) {
    Stack_Node* new_node_ptr = (Stack_Node*)malloc(sizeof(Stack_Node));
    new_node_ptr->data = data;
    if (empty_stack(stack_ptr)) {
        new_node_ptr->down = NULL;
        stack_ptr->top = new_node_ptr;
    } else {
        new_node_ptr->down = stack_ptr->top;
        stack_ptr->top = new_node_ptr;
    }
}

// pops the top node in the stack and returns the data stored in that node (not the node itself)
char pop (Char_Stack* stack_ptr) {
    assert (stack_ptr->top != NULL); // Can't pop an element from an empty stack

    Stack_Node* temp_node_ptr = stack_ptr->top;       // Record the current head of queue
    char data = temp_node_ptr->data;    // Record the data to be returned

    // Promote the 2nd node in the queue to the head of the queue
    stack_ptr->top = stack_ptr->top->down;

    free(temp_node_ptr);    // Free the memory of the dequeued node    

    return data;
}