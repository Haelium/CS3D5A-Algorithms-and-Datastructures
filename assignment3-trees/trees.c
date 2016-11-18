/*
trees.c, code implementing various tree functions
Author: David J. Bourke, Student Number: 12304135
Date started:   18th of November 2016
Date submitted:
Depends on: quicksort.h
*/

#include <stdlib.h>
#include <stdio.h>
#include "quicksort.h"

typedef struct Tree_Node Tree_Node;
struct Tree_Node {
    char data;
    Tree_Node* left;
    Tree_Node* right;
};

// Inserts node into a binary search tree, maintaining the valid BST properties
// this function does not maintain or require a balanced tree
void tree_insert (Tree_Node* root, char data) {
    if (root->data > data) {    // if data < root, insert left

        if (root->left == NULL) {
            // if we're at the base of the tree, create the node
            root->left = (Tree_Node*)malloc(sizeof(Tree_Node));
            root->left->data = data;
            return;
        } else {
            // if we're not at the base of the tree, keep moving down
            tree_insert(root->left, data);
        }

    } else {    // if data >= root, insert right

        if (root->right == NULL) {
            // if we're at the base of the tree, create the node
            root->right = (Tree_Node*)malloc(sizeof(Tree_Node));
            root->right->data = data;
            return;
        } else {
            // if we're not at the base of the tree, keep moving down
            tree_insert(root->right, data);
        }

    }   // end if (root->data > data)
}

Tree_Node* tree_search (Tree_Node* root, char data) {
    if (root == NULL) { // data not found, return NULL
        return NULL;
    }
    // If data found in this node, return pointer to this node
    if (root->data == data) { 
        return root;
    } else if (data < root->data) { // if data < root->data, search left child
        return tree_search(root->left, data);
    } else {    // if data > root->data, search right child
        return tree_search(root->right, data);
    }
}

void tree_print_sorted (Tree_Node* root) {
    if (root == NULL) {
        return;
    }
    tree_print_sorted(root->left);
    printf("%c (%d), ", root->data, root->data);
    tree_print_sorted(root->right);
}

void tree_delete (Tree_Node* root) {
    if (root == NULL) { // if null, don't delete anything
        return;
    }
    tree_delete(root->right);   // delete child & subchildren
    tree_delete(root->left);    // delete child & subchildren
    free(root);                 // delete self
}

Tree_Node* tree_create (char data) {
    // Create root node (no function to do this)
    Tree_Node* root = (Tree_Node*)malloc(sizeof(Tree_Node));
    root->data = data;
    root->left = NULL;
    root->right = NULL;
    return root;
}

// Creates a balanced BST assuming sorted_array is really sorted,
// if sorted_array is not sorted, then will create a balanced tree (not a BST)
Tree_Node* array_to_balanced_tree (char* array, int start, int end) {

    // The middle element of the input array (bounded by start and end)
    // is selected. This middle element becomes the root value of the node to be returned by the function.
    Tree_Node* root;
    int mid;

    if (start > end) {  // arrays cannot end before they start
        return NULL;
    }

    // The midpoint (between start and end) will be the root of this (sub)tree
    mid = (start + end) / 2;
    root = (Tree_Node*)malloc(sizeof(Tree_Node));
    root->data = sorted_array[mid];

    // The function calls itself recursively using the bottom half of the array (start -> mid - 1) as input
    // and the node returned by this recursive function call becomes the left child of the root
    root->left = array_to_balanced_tree(array, start, mid - 1);
    // The function calls itself recursively using the top half of the array (mid + 1 -> end) as input
    // and the node returned by this recursive function call becomes the right child of the root
    root->right = array_to_balanced_tree(array, mid + 1, end);

    // When the left and right children have been assigned, the function finishes by returning the root node.
    // The left and right chid, being assigned using the same process, are roots of balanced sub-trees within the super-tree
    return root;
}

Tree_Node* array_to_BST (char* array, int array_length) {
    quicksort(array, array_length);
    return array_to_balanced_tree(array, 0, array_length - 1);
}

// Returns the number of levels in the tree
// (We can use this to verify that the tree is balanced)
int tree_count_levels (Tree_Node* root) {
    int levels_left = 0, levels_right = 0;

    if (root == NULL) { // Null nodes not counted as levels
        return 0;
    }

    // Count the levels in each child subtree
    levels_left = tree_count_levels(root->left);
    levels_right = tree_count_levels(root->right);

    // Return the maximum number of levels between the two child subtrees
    if (levels_left > levels_right) {
        return levels_left + 1;
    } else {
        return levels_right + 1;
    }
}

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

    search_result_node = tree_search(root, 'E');
    printf("This should be E: %c\n", search_result_node->data);

    tree_print_sorted(root);
    printf("\n");

    tree_delete(root);

    printf("Testing balanced tree functions...\n");
    root = array_to_BST(test_array, 7);
    tree_print_sorted(root);
    printf("\n");
    printf("Levels in balanced tree: %d\n", tree_count_levels(root));

    tree_delete(root);
}