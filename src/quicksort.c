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
    
    char* a1 = (char *) a;
    char* b1 = (char *) b;
    
    char temp;
    int index = 0;
    
    while (*(a1 + index) != '\0' ){
	    temp = *(a1 + index);
	    *(a1 + index) = *(b1 + index);
	    *(b1 + index) = temp;
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

	array = (char *) array; //casts array to a char*
    	char * pivot = (char *) array + (elem_sz * right); //pointer to the rightmost element
    
	int index = left; //saves index of leftmost element
    	
	for (int i = left; i < right; i++){//iterates through all of the indexes
        	
		char * current = (char *) array + (elem_sz * i);//sets current to next unsorted element
        	
		if (cmp(current, pivot) < 0){ //compares current to pivot
            		index++;
			//need to convert to char * in order to do arithmetic
			swap(current, (char *) array + (elem_sz * index), (right - left));//swaps if necessary
        	}
    	}
   	swap((char *) array + (elem_sz * left), (char *) array + (elem_sz * index), (right - left)); 
	return index;//returns the (now) index of the pivot pointer
}

/**
 * Sorts with lomuto partitioning, with recursive calls on each side of the
 * pivot.
 * This is the function that does the work, since it takes in both left and
 * right index values.
 */
static void quicksort_helper(void *array, int left, int right, size_t elem_sz,
                             int (*cmp) (const void*, const void*)) {
    if(left  < right){ //not the base case
	int partition = lomuto(array, left, right, elem_sz, cmp); //index of the partition
	quicksort_helper(array, left, partition - 1, elem_sz, cmp); //recursive call for left side
	quicksort_helper(array, partition, right, elem_sz, cmp); //recursive call for right side
	}
}
