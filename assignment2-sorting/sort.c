#include <stdio.h>

#include "quicksort.h"
#include "heapsort.h"

int test_array[] = {
    4, 3, 28, 13, 12, 96, 1, 7, 8, 9, 4, 2, 0, 1, 
    22, 32, 33, 23, 54, 6, 32, 76, 39, 68, 39, 54
};

int main (void) {
    int ta_length = sizeof(test_array) / sizeof(test_array[0]);
    quicksort(test_array, 0, ta_length - 1);
    for (int x = 0; x < ta_length; x++) {
        printf("%d-", test_array[x]);
    }
    printf("\n");

    heapify(test_array);
}