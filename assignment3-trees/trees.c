/*
trees.c, code testing various tree functions from "tree_functions.h"
Author: David J. Bourke, Student Number: 12304135
Date started:   18th of November 2016
Date submitted:
Depends on: tree_functions.h, quicksort.h
*/

#include <stdio.h>
#include "tree_functions.h" // array_to_BBST, tree*, Tree_Node definition

int main (void) {
    // Test array used to test array_to_BBST
    char test_array[7] = {
        'X', 'Z', 'C', 'B', 'A', 'Y', 'F'
    };

    // Testing tree_create, tree_insert, and tree_print_sorted
    Tree_Node* root = tree_create('E');

    tree_insert(root, 'A');
    tree_insert(root, 'B');
    tree_insert(root, 'C');
    tree_insert(root, 'D');
    tree_insert(root, 'E');
    tree_insert(root, 'F');
    tree_insert(root, 'G');

    printf("This should be E: %c\n", tree_search(root, 'E')->data);
    tree_print_sorted(root);
    printf("\n");
    // For an unbalanced tree containing 7 nodes, tree_count_levels should return n >= 3
    printf("Levels in unbalanced tree: %d\n", tree_count_levels(root));

    tree_delete(root);  // deletes all nodes, but not the root pointer


    // Testing array_to_BBST
    printf("Testing balanced tree functions...\n");
    root = array_to_BBST(test_array, 7);    // resets root pointer to newly allocated memory
    tree_print_sorted(root);
    printf("\n");
    // for a balanced tree containing 7 nodes, tree_count_levels should return 3
    printf("Levels in balanced tree: %d\n", tree_count_levels(root));

    tree_delete(root);  // deletes all nodes, but not the root pointer
}