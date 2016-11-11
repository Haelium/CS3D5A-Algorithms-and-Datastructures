#include <stdlib.h>

// Heap associations for 0 indexed array
#define Parent(i)   (i-1) / 2
#define LChild(i)   2 * i + 1
#define RChild(i)   2 * i + 2

static inline void swap_int(int* x, int* y) {
    int swap = *x;
    *x = *y;
    *y = swap;
}

// Algorithm taken from pg. 154 of CLRS
void maxHeapify (int* array, int heap_size, int i) {
    int largest;
    int l = LChild(i);
    int r = RChild(i);
    if (l < heap_size && array[l] > array[i]) {
        largest = l;
    } else {
        largest = i;
    }
    if (r < heap_size && array[r] > array[largest]) {
        largest = r;
    }
    if (largest != i) {
        swap_int(&array[i], &array[largest]);
        maxHeapify(array, heap_size, largest);
    }
}


// Algorithm taken from pg. 157 of CLRS
void buildMaxHeap (int* array, int array_length) {
    int heap_size = array_length - 1;
    for (int i = array_length / 2 - 1; i >= 0; i--) {
        maxHeapify(array, heap_size, i);
    }
}

// Algorithm taken from pg. 160 of CLRS
void heapsort (int* array, int array_length) {
    int heap_size = array_length - 1;
    buildMaxHeap(array, array_length);
    for (int i = heap_size; i >= 1; i--) {
        swap_int(&array[0], &array[i]);
        maxHeapify(array, --heap_size, 0);
    }
}