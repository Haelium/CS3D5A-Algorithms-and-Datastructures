static inline int partition (int* array, int lo, int hi) {
    // Start at last element
    int pivot = array[lo];
    int i = lo - 1;
    int j = hi + 1;
    int swap;
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

        swap = array[i];
        array[i] = array[j];
        array[j] = swap;
    }
}

// If hi is greater than the length of the array, things will break
void quicksort (int* array, int lo, int hi) {
    int p;
    if (lo < hi) {
        p = partition(array, lo, hi);
        quicksort(array, lo, p);
        quicksort(array, p + 1, hi);
    }
}
