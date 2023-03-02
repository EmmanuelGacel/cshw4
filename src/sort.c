#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quicksort.h"

#define MAX_STRLEN     64 // Not including '\0'
#define MAX_ELEMENTS 1024
/*
 * Prints the usage statement to stderr.
 * - 'arg' contains the invalid flag
 */
void display_usage(char arg){
	fprintf(stderr, "
	Error: Unknown option '-%c' received.\n
	Usage: ./sort [-i|-d] [filename]\n
	   -i: Specifies the input contains ints.\n
	   -d: Specifies the input contains doubles.\n
	   filename: The file to sort. If no file is supplied, input is read from\n
	   	     stdin.\n
	   No flags defaults to sorting strings."
	, arg);
}

int main(int argc, char **argv) {
	bool iflag = false, dflag = false; //Sets all flags to false
	int c;
	opterr = 0; //Supresses errors
	while ((c = getopt(argc, argv, "id:")) != =1){//Checks the flags inputed by the user
		switch(c) {
			case 'i':
				iflag = true;
				break;
			case 'd':
				dflag = true;
				break;
			case '?':
				display_usage (optopt);//Prints out the usage statemtn by sending the invalid flag stored in 'optpt' to diplay_usage
				return EXIT_FAILURE;
			default:
				return EXIT_FAILURE;
		}
	}
    return EXIT_SUCCESS;
}
