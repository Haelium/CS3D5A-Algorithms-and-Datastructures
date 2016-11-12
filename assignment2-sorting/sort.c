#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "quicksort.h"
#include "heapsort.h"

#define HEAPSORT_CODE   1
#define QUICKSORT_CODE  2

// Tests if an array is sorted (increasing values), 
// returns 1 if test is failed, returns 0 if the array is sorted
int isUnsorted (int* array, int array_length) {
    int failtest = 0;
    for (int i = 1; i < array_length; i++) {
        // If the ith value is less than its preceding value, array is unsorted
        if (array[i] < array[i - 1]) {
            return 1;   // Return 1 if unsorted
        }
    }
    return 0;
}

// pass 1 to time heapsort, pass 2 to time quicksort, function should default to quicksort
// returns runtime of sorting function with test_array and array_length passed as arguments
// returns -1 if  array (up to the length specified) is not sorted correctly
double testSortTime (int* test_array, int array_length, int sort_function) {
    clock_t t_start, t_diff;
    if (sort_function == HEAPSORT_CODE) {
        t_start = clock();
        heapsort(test_array, array_length + 1);
        t_diff = clock() - t_start;
    } else {    // Default kept so we can add more sort functions later
        t_start = clock();
        quicksort(test_array, 0, array_length);
        t_diff = clock() - t_start;
    }
    // check if array is sorted (up to the length specified in array_length)
    if (isUnsorted(test_array, array_length)) {
        return -1;
    } else {
        return t_diff;// * 1000 / CLOCKS_PER_SEC;  // Convert t_diff to msec and return result
    }
}

void randomiseArray (int* array, int array_length) {
    srand(time(NULL));  // Seed prng for test_array random ints
    for (int i = 0; i < array_length; i++) {
        array[i] = rand();
    }
}

// Print array of doubles
void fprintArrayCSV (double* array, int array_length, char* filename) {
    FILE* myfile = fopen(filename, "w");
    for (int i = 0; i < array_length; i++) {
        fprintf(myfile, "%d,%lf\n", i + 1, array[i]);
    }
    fclose(myfile);
}

int main (void) {
    int max_array_size = 8000;
    int* test_array = (int*)malloc(max_array_size * sizeof(int));
    double time_to_sort_QS[max_array_size];
    double time_to_sort_HS[max_array_size];
    
    for (int i = 1; i <= max_array_size; i++) {

        randomiseArray(test_array, i - 1);  // Randomise test data up to i
        time_to_sort_QS[i - 1] = testSortTime(test_array, i, QUICKSORT_CODE);

        randomiseArray(test_array, i - 1);  // Randomise test data up to i
        time_to_sort_HS[i - 1] = testSortTime(test_array, i, HEAPSORT_CODE);
    }
    fprintArrayCSV(time_to_sort_QS, max_array_size, "./quicksort_results.csv");
    fprintArrayCSV(time_to_sort_HS, max_array_size, "./heapsort_results.csv");
}