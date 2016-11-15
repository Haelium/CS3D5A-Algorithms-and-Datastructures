#include <stdlib.h>

// Heap associations for 0 indexed array
#define Parent(i)   (i-1) / 2
#define LChild(i)   2 * i + 1
#define RChild(i)   2 * i + 2

// Each comparison of any element of the array shall be refered to as a "probe"
// This "probecounting" is not part of the heapsort algorithm
static int num_of_probes;

static inline void swap_int (int* x, int* y) {
    int swap = *x;
    *x = *y;
    *y = swap;
}

// Algorithm taken from pg. 154 of CLRS
// Exchanges the value of parent with the largest child if the largest child's value is greater than parent
static void maxHeapify (int* array, int heap_size, int parent) {
    int largest = 0;
    int left_child = LChild(parent);
    int right_child = RChild(parent);

    num_of_probes++;    // array[l] compared with array[i]
    // If the value of the left child is greater than the parent, assign left_child as largest
    if (left_child < (heap_size) && array[left_child] > array[parent]) {
        largest = left_child;
    } else {
        largest = parent;
    }

    num_of_probes++;    // array[r] sompared with array[largest]
    // If the right child is larger than the left child or the parent, assign right_child as largest
    if (right_child < (heap_size) && array[right_child] > array[largest]) {
        largest = right_child;
    }
    // If a child is larger than the parent, exchange values and heapify the new child
    if (largest != parent) {
        swap_int(&array[parent], &array[largest]);
        maxHeapify(array, heap_size, largest);
    }
}

// Algorithm taken from pg. 157 of CLRS
static inline void buildMaxHeap (int* array, int heap_size) {
    // Start loop from the second to last row and work backwards to the root, max-heapifying each element
    for (int i = heap_size / 2 - 1; i >= 0; i--) {
        maxHeapify(array, heap_size, i);
    }
}

// Algorithm taken from pg. 160 of CLRS
int heapsort (int* array, int heap_size) {
    num_of_probes = 0;  // reset probe counter
    buildMaxHeap(array, heap_size);
    for (int i = heap_size - 1; i > 0; i--) {
        // Exchange root of the heap with the last element
        swap_int(&array[0], &array[i]);
        // Call maxHeapify again, reducing the size of the heap to exclude the previous root which was replaced with i
        maxHeapify(array, --heap_size, 0);
    }
    return num_of_probes;
}
