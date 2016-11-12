#include <stdlib.h>

// Heap associations for 0 indexed array
#define Parent(i)   (i-1) / 2
#define LChild(i)   2 * i + 1
#define RChild(i)   2 * i + 2

static int num_of_probes;

static inline void swap_int (int* x, int* y) {
    int swap = *x;
    *x = *y;
    *y = swap;
}

// Algorithm taken from pg. 154 of CLRS
static void maxHeapify (int* array, int heap_size, int i) {
    int largest = 0;
    int l = LChild(i);
    int r = RChild(i);
    if (l <= (heap_size - 1) && array[l] > array[i]) {
        largest = l;
    } else {
        largest = i;
    }
    if (r <= (heap_size - 1) && array[r] > array[largest]) {
        largest = r;
    }
    if (largest != i) {
        swap_int(&array[i], &array[largest]);
        maxHeapify(array, heap_size, largest);
    }
    num_of_probes++;
}

// Algorithm taken from pg. 157 of CLRS
static inline void buildMaxHeap (int* array, int heap_size) {
    for (int i = heap_size / 2 - 1; i >= 0; i--) {
        maxHeapify(array, heap_size, i);
    }
}

// Algorithm taken from pg. 160 of CLRS
int heapsort (int* array, int heap_size) {
    num_of_probes = 0;
    buildMaxHeap(array, heap_size);
    for (int i = heap_size - 1; i > 0; i--) {
        swap_int(&array[0], &array[i]);
        maxHeapify(array, --heap_size, 0);
    }
    return num_of_probes;
}
