// Each comparison of any two element of the array shall be refered to as a "probe"
// This "probecounting" is not part of the quicksort algorithm
static int num_of_probes;

static inline int partition (int* array, int lo, int hi) {
    // Start at last element
    int pivot = array[lo];
    int i = lo - 1; // iterator starting at lo
    int j = hi + 1; // decrementer starting at hi
    int swap;
    while (1) {

        do {
            i = i + 1;
            num_of_probes++;    // array[i] compared with pivot
        } while (array[i] < pivot);
        
        do {
            j = j - 1;
            num_of_probes++;    // array[j] compared with pivot
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

// If hi is greater than the length of the array, things will break
static void private_quicksort (int* array, int lo, int hi) {
    int p;
    if (lo < hi) {
        p = partition(array, lo, hi);
        private_quicksort(array, lo, p);
        private_quicksort(array, p + 1, hi);
    }
}

// Wrapper function, returns number of probes and provides cleaner interface
int quicksort (int* array, int array_length) {
    num_of_probes = 0;
    private_quicksort(array, 0, array_length - 1);
    return num_of_probes;
}