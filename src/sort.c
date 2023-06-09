#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quicksort.h"

/*
 * HW4 Team 25, March 10, 2022
 */


#define MAX_STRLEN     64 // Not including '\0'
#define MAX_ELEMENTS 1024

/*
 * Prints the usage statement to stderr.
 * - 'arg' contains the invalid flag
 */
void display_usage(char arg){
	
	fprintf(stderr, "Error: Unknown option '-%c' received.\nUsage: ./sort [-i|-d] [filename]\n   -i: Specifies the input contains ints.\n   -d: Specifies the input contains doubles.\n   filename: The file to sort. If no file is supplied, input is read from \n             stdin.\n   No flags defaults to sorting strings.\n",arg);
}

/**
 * Takes as input a string and an in-out parameter value.
 * If the string can be parsed, the integer value is assigned to the value
 * parameter and true is returned.
 * Otherwise, false is returned and the best attempt to modify the value
 * parameter is made.
 */
int get_integer(char *input, int *value) {
    long long long_long_i;
    if (sscanf(input, "%lld", &long_long_i) != 1) {
        fprintf(stderr, "Error: Cannot convert '%s' to integer.\n", input);
        return 0;
    }
    *value = (int)long_long_i;
    if (long_long_i != (long long)*value) {
        fprintf(stderr, "Warning: Integer overflow with '%s'.\n", input);
        return 0;
    }
    return 1;
}
/**
 * Takes as input a string and an in-out parameter value.
 * If the string can be parsed, the integer value is assigned to the value
 * parameter and true is returned.
 * Otherwise, false is returned and the best attempt to modify the value
 * parameter is made.
 */
int get_double(char *input, double *value) {
    if (sscanf(input, "%lf", value) != 1) {
        fprintf(stderr, "Error: Cannot convert '%s' to double.\n", input);
        return 0;
    }
    //decimals do not overflow, just a loss in precision
    return 1;
}


int main(int argc, char **argv) {
	int iflag = 0; 
	int dflag = 0; //Sets all flags to false
	int c;
	int file_flag = 0;
	opterr = 0; //Supresses errors
	while ((c = getopt(argc, argv, ":id")) != -1){//Checks the flags inputed by the user
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
	}
	//This section is responsible for reading from stdin
	if(file_flag == 0){
		if(iflag == 1){//Reads integers from stdin
			int i = 0;
			int num;
			
			int *buffer = (int*) malloc(MAX_ELEMENTS * sizeof(int));
			if (buffer == NULL) {
	                        fprintf(stderr, "Error: malloc failed\n");
        	                exit(EXIT_FAILURE);
                	}

			//CHECK FOR INVALID OR OVERFLOW HERE
                	while(scanf("%d", &num) != EOF && i < MAX_ELEMENTS){
                        	buffer[i] = num;
                        	i++;
			}
			
			quicksort(buffer, i, sizeof(int), int_cmp);
			for(int j = 0; j< i; j++){
				 printf("%d\n", buffer[j]);
			}
			free(buffer);

		}else if(dflag == 1){//Reads doubles from stdin
			int i = 0;
                	double num;
                	
			double *buffer = (double*) malloc(MAX_ELEMENTS * sizeof(double));
			if (buffer == NULL) {
	                        fprintf(stderr, "Error: malloc failed\n");
        	                exit(EXIT_FAILURE);
               		 }

                	while(scanf("%lf", &num) != EOF && i < MAX_ELEMENTS){
                        	buffer[i] = num;
                        	i++;
                	}
			quicksort(buffer, i, sizeof(double), dbl_cmp);
		       	for(int j = 0; j< i; j++){
                        	printf("%lf\n", buffer[j]);
			}
			free(buffer);

                }else{//Reads strings from stdin
		
                int i = 0;
                char** buffer = (char**) malloc(MAX_ELEMENTS * sizeof(char)); //malloc + free this
		if (buffer == NULL) {
        		fprintf(stderr, "Error: malloc failed\n");
        		exit(EXIT_FAILURE);
    		}
		//USE MACRO AND ADD 1
		char *word = (char*) malloc(sizeof(char) * MAX_STRLEN + 1); // allocate memory for word
		if (word == NULL) {
        		fprintf(stderr, "Error: malloc failed\n");
        		exit(EXIT_FAILURE);
    		}	
		while(scanf("%63[^\n]", word) !=  EOF){
   			scanf("%*[^\n]"); // gets rid of the remaining line
    			scanf("%*c"); // gets rid of the newline character
    			buffer[i] = word;
    			i++;
   		 word = (char*) malloc(sizeof(char) * MAX_STRLEN + 1); //makes memory for the next word if needed
		if (word == NULL) {
                        fprintf(stderr, "Error: malloc failed\n");
                        exit(EXIT_FAILURE);
                }
		}
		quicksort(buffer,i, sizeof(char*), str_cmp);

		for(int j = 0; j< i; j++){
    			printf("%s\n", buffer[j]);
		}

		for (int j = 0; j < i; j++) { //frees all of the array elements
    			free(buffer[j]);
		}

		free(word); //frees last block (which was malloced and not filled)
		free(buffer); //frees the array of char*'s 
		}
	}else{
		//FILE READING
		char buffer[MAX_STRLEN + 1];
		FILE * fp;
		if ((fp = fopen(argv[argc-1], "r")) == NULL){//Attemps to open a file
			fprintf(stderr, "Error: Cannot open '%s'. No such file or directory.\n", argv[argc-1]);
                        return EXIT_FAILURE;
		}
		
		if(iflag == 1){ // ints from file
			int num_ints = 0;
			int *intarray = (int*) malloc(MAX_ELEMENTS * sizeof(int));

			if (intarray  == NULL) {
	                        fprintf(stderr, "Error: malloc failed\n");
        	                exit(EXIT_FAILURE);
                	}

			while (fgets(buffer, MAX_STRLEN, fp)){
    				char *eoln = strchr(buffer, '\n');
		        	if (eoln != NULL) {
        				*eoln = '\0';
    				}

   				int int_val;
    				if (get_integer(buffer, &int_val)) {
        				intarray[num_ints] = int_val;
        				num_ints++;
    				}
			}

			quicksort(intarray, num_ints, sizeof(int), int_cmp);
		
			for(int i = 0; i < num_ints; i++){
                		printf("%d\n", intarray[i]);
			}

			free(intarray); //frees the int array
			fclose(fp);
		}
		else if(dflag == 1){ //doubles from file
			int num_ints = 0;
                        double *dblarray = (double*) malloc (MAX_ELEMENTS * sizeof(double));
			
			if (dblarray == NULL) {
                	        fprintf(stderr, "Error: malloc failed\n");
        	                exit(EXIT_FAILURE);
	                }

                         while (fgets(buffer, MAX_STRLEN, fp)){
                                char *eoln = strchr(buffer, '\n');
                                if (eoln != NULL) {
                                *eoln = '\0';
                                }

                        double dbl_val;
			if (get_double(buffer, &dbl_val)) {
                                dblarray[num_ints] = dbl_val;//Modified code
                                num_ints++;
                        }
			}
			quicksort(dblarray, num_ints, sizeof(double), dbl_cmp);
			for(int i = 0; i < num_ints; i++){
                		printf("%lf\n", dblarray[i]);
		        }
			free(dblarray);
			fclose(fp);
		}
		else{ //strings from file
			int num_words = 0;
                        
			char **strarray = (char**) malloc(MAX_ELEMENTS * sizeof(char*));
			if (strarray == NULL) {
	                        fprintf(stderr, "Error: malloc failed\n");
        	                exit(EXIT_FAILURE);
                	}

                        while (fgets(buffer, MAX_STRLEN, fp)){
                                char *eoln = strchr(buffer, '\n');
                                if (eoln != NULL) {
                                *eoln = '\0';
                                }

				char* word = malloc(sizeof(char) * MAX_STRLEN + 1);
                        	if (word == NULL) {
		                        fprintf(stderr, "Error: malloc failed\n");
                		        exit(EXIT_FAILURE);
                		}

				if(sscanf(buffer, "%s", word) != EOF){
					strarray[num_words] = word;
	                        	num_words++;
                        	}
			}
			quicksort(strarray, num_words, sizeof(char*), str_cmp);
                        for(int i = 0; i < num_words; i++){
                                printf("%s\n", strarray[i]);
                        }

			for (int i = 0; i < num_words; i++) {
    				free(strarray[i]);
			}
			free(strarray);
			fclose(fp);
		}
	}
	return EXIT_SUCCESS;
}
