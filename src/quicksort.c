#include <stdio.h>
#include <string.h>
#include "quicksort.h"

/* Static (private to this file) function prototypes. */
static void swap(void *a, void *b, size_t size);
static int lomuto(void *array, int left, int right, size_t elem_sz,
                  int (*cmp) (const void*, const void*));
static void quicksort_helper(void *array, int left, int right, size_t elem_sz,
                             int (*cmp) (const void*, const void*));
//working version
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
    
    for(int i = 0; i < size; i++){
    	temp = a1[i];
	a1[i] = b1[i];
	b1[i] = temp;
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
    	char * pivot = (char *) array + (elem_sz * left); //pointer to the leftmost element
    
	int index = left; //saves index of leftmost element
	for (int i = left+1; i <= right; i++){//iterates through all of the indexes
		char * current = (char *) array + (elem_sz * i);//sets current to next unsorted element
        	
		if (cmp(current, pivot) < 0){ //compares current to pivot
            		index++;
			//need to convert to char * in order to do arithmetic
			swap((char *) array + (elem_sz * index),current,elem_sz);//swaps if necessary
        	}
    	}
	swap(pivot, (char *) array + (elem_sz * index), elem_sz);

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
	quicksort_helper(array, partition + 1, right, elem_sz, cmp); //recursive call for right side
	}
    /*
     * Should the second quicksort call be: quicksort_helper(array, partition, right, elem_sz, cmp);
     */
}

int int_cmp(const void *a, const void *b){
	int result = *((int *) a) - *((int *) b);
	if (result > 0) return 1;
	else if (result < 0) return -1;
	else return 0;
}
int dbl_cmp(const void *a, const void *b){
	double result = *((double *) a) - *(( double *)b);
	if (result > 0) return 1;
	else if (result < 0) return -1;
	else return 0;
}

int str_cmp(const void *a, const void *b){
	return strcmp((const char *) a, (const char *) b);
}

void quicksort(void *array, size_t len, size_t elem_sz, int (*cmp) (const void*, const void*)){
	quicksort_helper(array, 0, (len - 1), elem_sz, cmp);

}
