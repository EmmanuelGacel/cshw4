#include <stdio.h>
#include <string.h>
#include "quicksort.h"

/* Static (private to this file) function prototypes. */
static void swap(void *a, void *b, size_t size);
static int lomuto(void *array, int left, int right, size_t elem_sz,
                  int (*cmp) (const void*, const void*));
static void quicksort_helper(void *array, int left, int right, size_t elem_sz,
                             int (*cmp) (const void*, const void*));

/**
 * Swaps the values in two pointers.
 *
 * Casts the void pointers to type (char *) and works with them as char pointers
 * for the remainder of the function. Swaps one byte at a time, until all 'size'
 * bytes have been swapped. For example, if ints are passed in, size will be 4
 * and this function will swap 4 bytes starting at a and b pointers.
 */
static void swap(void *a, void *b, size_t size) {
    // TODO
    a = (char *) a;
    b = (char *) b;
    char temp;
    int index = 0;
    while ((temp = *(a + i)) != 0 ){
	    *(a + i) = *(b + i);
	    *(b + i) = temp;
	    index = index + size;
    }
}

/**
 * Partitions array around a pivot, utilizing the swap function. Each time the
 * function runs, the pivot is placed into the correct index of the array in
 * sorted order. All elements less than the pivot should be to its left, and all
 * elements greater than or equal to the pivot should be to its right.
 */
static int lomuto(void *array, int left, int right, size_t elem_sz,
                  int (*cmp) (const void*, const void*)) {
    // TODO
    array = (char *) array;
    char * pivot = array[elem_sz * left];
    int current = left * elem_sz; // Is current a number or a pointer?
    //char * current = *(array + (left * elem_sz));
    for (char * i = current + elem_sz, index <= right * elem_sz, i = i + elem_sz){
	    if (cmp(pivot, i) > 1){
		    s = s + elem_sz;
		    swap(array[s], array[i]);
	    }
    }
    swap(array[left*elem_sz], array[s]);
    return current;
}

/**
 * Sorts with lomuto partitioning, with recursive calls on each side of the
 * pivot.
 * This is the function that does the work, since it takes in both left and
 * right index values.
 */
static void quicksort_helper(void *array, int left, int right, size_t elem_sz,
                             int (*cmp) (const void*, const void*)) {
    // TODO
}
