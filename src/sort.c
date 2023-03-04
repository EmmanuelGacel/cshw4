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
	
	fprintf(stderr, "Error: Unknown option '-%c' received.\nUsage: ./sort [-i|-d] [filename]\n   -i: Specifies the input contains ints.\n   -d: Specifies the input contains doubles.\n   filename: The file to sort. If no file is supplied, input is read from \n              stdin.\n   No flags defaults to sorting strings.\n",arg);
}

int main(int argc, char **argv) {
	int iflag = 0; 
	int dflag = 0; //Sets all flags to false
	int c;
	int file_flag = 0;
	int bytes = 0;
	opterr = 0; //Supresses errors
	while ((c = getopt(argc, argv, ":id")) != -1){//Checks the flags inputed by the user
		printf("c: %c\n", c);
		switch(c) {
			case 'i':
				iflag = 1;
				break;
			case 'd':
				dflag = 1;
				break;
			default:
				display_usage (optopt);//Prints out the usage statemtn by sending the invalid flag stored in 'optpt' to diplay_usage
				return EXIT_FAILURE;
		}
	}
	printf("iflag: %d\ndflag:  %d\n", iflag, dflag);
	  int total_flags = iflag + dflag;
        if (total_flags == 2){//Checks to see if too many flags were specified
                fprintf(stderr, "Error: Too many flags specified.\n");
                return EXIT_FAILURE;
        }else if(total_flags == 0 && argc > 2){//Checks to see if too many files were specified
                fprintf(stderr, "Error: Too many files specified.\n");
                return EXIT_FAILURE;
        }else if(total_flags == 1 && argc > 3){//Checks to see if too many files were specified
                fprintf(stderr, "Error: Too many files specified.\n");
                return EXIT_FAILURE;
        }else if(total_flags == 0 && argc == 2){//Checks to see if a file was specified
                file_flag = 1;
        }else if(total_flags == 1 && argc == 3){//Checks to see if a file was specified
                file_flag = 1;
        }else if(iflag == 1){//Specifies that we are processing integers
		bytes = sizeof(int);
	}
	else if(dflag == 1){//Specifies that we are processing doubles
                bytes = sizeof(double);
        }
        else{//Specifies that we are processing strings
                bytes = sizeof(char);
        }
	printf("File_flag: %d\n", file_flag);
	printf("Sizeof bytes: %d\n", bytes);
	//This section is responsible for reading from stdin
	if(file_flag == 0){
		if(iflag == 1){//Reads integers from stdin
			printf("Made it to stdin integer processsor \n");
			int i = 0;
			int num;
                	int buffer[1024];
                	while(scanf("%d", &num) != EOF){
                        	buffer[i] = num;
                        	i++;
			}
			 for(int j = 0; j< i; j++){
				 printf("%d\n", buffer[j]);
			 }

		}else if(dflag == 1){//Reads doubles from stdin
			printf("Made it to stdin doubles processsor \n");
			/*
			int i = 0;
                	double num;
                	double buffer[1024];
                	while(scanf("%lf`", &num) != EOF){
                        	buffer[i] = num;
                        	i = i + bytes;
                	} for(int j = 0; j< i; j++){
                        printf("%lf\n", buffer[j]);
			*/
                }else{//Reads strings from stdin
			printf("Made it to stdin string processsor \n");
		}
	}else{
		//This section is responsible for reading from a file
                printf("Made it to stdin file processsor \n");
		FILE * fp;
		if ((fp = fopen(argv[argc], "r")) == NULL){//Attemps to open a file, if it can't the designated error message is printed.
			fprintf(stderr, "Error: Cannot open source file '%s'. %s.\n", argv[argc], strerror(errno));
                        return EXIT_FAILURE;
		}
        }

	/*
	//SCANS INTEGERS FROM STDIN
	if(argc < 3){
		int i = 0;
		int num;
		int buf[1024];
		while(scanf("%d", &num) != EOF){
			buf[i] = num;
			i++;
		}
		for(int j = 0; j< i; j++){
			printf("%d\n", buf[j]);
		}
	}
	*/
    return EXIT_SUCCESS;
}
