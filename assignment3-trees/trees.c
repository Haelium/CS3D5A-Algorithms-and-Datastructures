/*
trees.c, code testing various tree functions from "tree_functions.h"
Author: David J. Bourke, Student Number: 12304135
Date started:   18th of November 2016
Date submitted:
Depends on: tree_functions.h, quicksort.h
*/

#include <stdio.h>
#include "tree_functions.h"

int main (void) {
    char test_array[7] = {
        'X', 'Z', 'C', 'B', 'A', 'Y', 'F'
    };

    Tree_Node* root = tree_create('E');
    Tree_Node* search_result_node;

    tree_insert(root, 'A');
    tree_insert(root, 'B');
    tree_insert(root, 'C');
    tree_insert(root, 'D');
    tree_insert(root, 'E');
    tree_insert(root, 'F');
    tree_insert(root, 'G');
    printf("Levels in unbalanced tree: %d\n", tree_count_levels(root));

    search_result_node = tree_search(root, 'E');
    printf("This should be E: %c\n", search_result_node->data);

    tree_print_sorted(root);
    printf("\n");

    tree_delete(root);

    printf("Testing balanced tree functions...\n");
    root = array_to_BBST(test_array, 7);
    tree_print_sorted(root);
    printf("\n");
    printf("Levels in balanced tree: %d\n", tree_count_levels(root));

    tree_delete(root);
}