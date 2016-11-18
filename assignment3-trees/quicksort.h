/*
quicksort.h, code implementing quicksort for character arrays
Author: David J. Bourke, Student Number: 12304135
Date started:   18th of November 2016
Date submitted:
Used in: trees.c
Based on code used in assignment2-sorting
*/

static inline int partition (char* array, int lo, int hi) {
    // Start at last element
    char pivot = array[lo];
    int i = lo - 1; // iterator starting at lo
    int j = hi + 1; // decrementer starting at hi
    char swap;
    while (1) {

        do {
            i = i + 1;
        } while (array[i] < pivot);
        
        do {
            j = j - 1;
        } while (array[j] > pivot);

        if (i >= j) {
            return j;
        }
        
        // Exchange array[i] with array[j]
        swap = array[i];
        array[i] = array[j];
        array[j] = swap;
    }
}

// Sorts elements of array. 
// lo is the lowest index to be sorted, hi is highest index to be sorted.
static void private_quicksort (char* array, int lo, int hi) {
    char p;
    if (lo < hi) {
        p = partition(array, lo, hi);
        private_quicksort(array, lo, p);
        private_quicksort(array, p + 1, hi);
    }
}

// Wrapper function, returns number of probes and provides cleaner interface
void quicksort (char* array, int array_length) {
    private_quicksort(array, 0, array_length - 1);
}