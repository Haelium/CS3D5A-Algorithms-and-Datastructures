#include <stdio.h>

#include "quicksort.h"

int test_array[] = {4, 3, 1, 7, 8, 9, 4, 2, 0, 1};

int main (void) {
    quicksort(test_array, 0, 9);
    for (int x = 0; x < 10; x++) {
        printf("%d-", test_array[x]);
    }
    printf("\n");
}