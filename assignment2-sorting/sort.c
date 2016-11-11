#include <stdio.h>

#include "quicksort.h"
#include "heapsort.h"

// Tests if an array is sorted (increasing values), 
// returns 1 if test is failed, returns 0 if the array is sorted
int unsorted (int* array, int array_length) {
    int failtest = 0;
    for (int i = 1; i < array_length; i++) {
        // If the ith value is less than its preceding value, array is unsorted
        if (array[i] < array[i - 1]) {
            return 1;   // Return 1 if unsorted
        }
    }
    return 0;
}

int test_array[] = {
    4, 3, 28, 13, 12, 96, 1, 7, 8, 9, 4, 2, 0, 1, 
    22, 32, 33, 23, 54, 6, 32, 76, 39, 68, 39, 54
};

// Print array of ints
void print_array (int* array, int array_length) {
    for (int i = 0; i < array_length; i++) {
        printf("%d-", array[i]);
    }
    printf("\n");
}

int main (void) {
    int ta_length = sizeof(test_array) / sizeof(test_array[0]);
    //quicksort(test_array, 0, ta_length - 1);
    heapsort(test_array, ta_length);
    print_array(test_array, ta_length);
    printf("\n");

    
}