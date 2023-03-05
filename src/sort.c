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
        fprintf(stderr, "Error: Cannot convert %s to integer.\n", input);
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
        fprintf(stderr, "Error: Cannot convert %s to double.\n", input);
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
			
			int *buffer = (int*) malloc(MAX_ELEMENTS * sizeof(int));

                	while(scanf("%d", &num) != EOF && i < MAX_ELEMENTS){
                        	buffer[i] = num;
                        	i++;
			}
			//quicksort(&buffer, i, bytes, int_cmp);
			for(int j = 0; j< i; j++){
				 printf("%d\n", buffer[j]);
			}
			free(buffer);

		}else if(dflag == 1){//Reads doubles from stdin
			printf("Made it to stdin doubles processsor \n");
			int i = 0;
                	double num;
                	
			double *buffer = (double*) malloc(MAX_ELEMENTS * sizeof(double));

                	while(scanf("%lf", &num) != EOF){
                        	buffer[i] = num;
                        	i++;
                	}
			//quicksort(&buffer, i, bytes, dbl_cmp);
		       	for(int j = 0; j< i; j++){
                        	printf("%lf\n", buffer[j]);
			}
			free(buffer);

                }else{//Reads strings from stdin
		
		printf("Made it to stdin string processsor \n");
                int i = 0;
                char** buffer = (char**) malloc(MAX_ELEMENTS * sizeof(char)); //malloc + free this
		
		//USE MACRO AND ADD 1
		char *word = (char*) malloc(sizeof(char) * MAX_STRLEN + 1); // allocate memory for word
		while(scanf("%63[^\n]", word) !=  EOF){
   			scanf("%*[^\n]"); // gets rid of the remaining line
    			scanf("%*c"); // gets rid of the newline character
    			buffer[i] = word;
    			i++;
   		 word = (char*) malloc(sizeof(char) * MAX_STRLEN + 1); //makes memory for the next word if needed
		}
		
		//quicksort(&buffer, sizeof(char*), i, str_cmp);

		for(int j = 0; j< i; j++){
    			printf("Coming out: %s\n", buffer[j]);
		}

		for (int j = 0; j < i; j++) { //frees all of the array elements
    			free(buffer[j]);
		}

		free(word); //frees last block (which was malloced and not filled)
		free(buffer); //frees the array of char*'s 
		}
	}else{
		//FILE READING
                printf("Made it to stdin file processsor \n");
		char buffer[MAX_STRLEN + 1];
		FILE * fp;
		if ((fp = fopen(argv[argc-1], "r")) == NULL){//Attemps to open a file
			fprintf(stderr, "Error: Cannot open source file '%s'. %s.\n", argv[argc], strerror(errno));
                        return EXIT_FAILURE;
		}
		
		if(iflag == 1){ // ints from file
			int num_ints = 0;
			int *intarray = (int*) malloc(MAX_ELEMENTS * sizeof(int));

		while (fgets(buffer, MAX_STRLEN, fp)){
    			char *eoln = strchr(buffer, '\n');
		        if (eoln != NULL) {
        		*eoln = '\0';
    			}

   		int int_val;
    		if (get_integer(buffer, &int_val)) {
        		printf("Ints going into the array: %d\n", int_val);
        		intarray[num_ints] = int_val;
        		num_ints++;
    		}
		}

		//quicksort(&intarray, num_ints, sizeof(int), int_cmp);
		
		for(int i = 0; i < num_ints; i++){
                	printf("Ints comming out of the array: %d\n", intarray[i]);
		}

		free(intarray); //frees the int array

		}
		else if(dflag == 1){ //doubles from file
			int num_ints = 0;
                        double *dblarray = (double*) malloc (MAX_ELEMENTS * sizeof(double));

                         while (fgets(buffer, MAX_STRLEN, fp)){
                                char *eoln = strchr(buffer, '\n');
                                if (eoln != NULL) {
                                *eoln = '\0';
                                }

                        double dbl_val;
			if (get_double(buffer, &dbl_val)) {
                        	printf("Doubles going into the array: %lf\n", dbl_val);
                                dblarray[num_ints] = dbl_val;//Modified code
                                num_ints++;
                        }
			}
			//quicksort(&dblarray, num_ints, sizeof(double), dbl_cmp);
			for(int i = 0; i < num_ints; i++){
                		printf("Doubles comming out of the array: %lf\n", dblarray[i]);
		        }
			free(dblarray);
		}
		else{ //strings from file
			int num_words = 0;
                        
			char **strarray = (char**) malloc(MAX_ELEMENTS * sizeof(char*));

                        while (fgets(buffer, MAX_STRLEN, fp)){
                                char *eoln = strchr(buffer, '\n');
                                if (eoln != NULL) {
                                *eoln = '\0';
                                }

				char* word = malloc(sizeof(char) * MAX_STRLEN);
                        	if(sscanf(buffer, "%s", &*word) != 1){
                                	printf("String going into array: %s\n", word);
					strarray[num_words] = word;
	                        	num_words++;
                        	}
			}
			//quicksort(&strarray, num_words, sizeof(char*), str_cmp);
                        for(int i = 0; i < num_words; i++){
                                printf("Strings comming out of the array: %s\n", strarray[i]);
                        }

			for (int i = 0; i < num_words; i++) {
    				free(strarray[i]);
			}
			free(strarray);
		}
	/**
		int num_ints = 0;
    		int intarray1[MAX_ELEMENTS];//Modified code
    		double doublearray1[MAX_ELEMENTS];
		//char *stringarray1[MAX_ELEMENTS};
		// Reads at most n-1 characters from infile until a newline is found. The
       		//characters up to and including the newline are stored in buf. The buffer
       		//is terminated with a '\0'. 
    		while (fgets(buffer, MAX_STRLEN, fp)) { //PUTS INTO BUFFER FROM FILE
        		// Replace the '\n' with '\0'.
        		char *eoln = strchr(buffer, '\n');
        		if (eoln != NULL) {
            			*eoln = '\0';
       	 		}

        		int int_val;
			double d_val;

			if(iflag == 1){ //int
        			if (get_integer(buffer, &int_val)) {
                			printf("Ints going into the array: %d\n", int_val);
                			intarray1[num_ints] = int_val;//Modified code
                			num_ints++;
            			}
			}else if(dflag == 1){ //double
                                if (get_double(buffer, &d_val)) {
                                        printf("Doubles going into the array: %lf\n", d_val);
                                        doublearray1[num_ints] = d_val;//Modified code
                                        num_ints++;
                             	 }
			else{ //string
			      
			      	char* word = malloc(sizeof(char) * 64);
				if(sscanf(buffer, "%lf", value) != 1){
					printf("String going into array: %s\n", word);

				}
				stringarray[num_ints] = word;
				num_ints++;
				free(word);
				
				}	
                        }

    		} //QUICKSORTS AND PRINTS OUT OF BUFFER
		if(iflag == 1){ //int
			int intarray2[num_ints];
			
                 	* //Loads ints from array1 into an array of the correct size
                 	
	                for (int i = 0; i < num_ints; i++){
        	                intarray2[i] = intarray1[i];
                	}
			quicksort(&intarray2, num_ints, bytes, int_cmp);
			for(int i = 0; i < num_ints; i++){
                		printf("Ints comming out of the array: %d\n", intarray2[i]);
		        }
		}else if(dflag == 1){ //double
			double doublearray2[num_ints];
			
                 	// Loads ints from array1 into an array of the correct size
                 	
                	for (int i = 0; i < num_ints; i++){
                	        doublearray2[i] = doublearray1[i];
        	        }
			quicksort(&doublearray2, num_ints, bytes, int_cmp);
			for(int i = 0; i < num_ints; i++){
                		printf("Doubles comming out of the array: %lf\n", doublearray2[i]);
       			 }
		}else{ //string
		      
			char* stringarray2[num_ints]; //correctly sized array

			for(int i = 0; i < num_ints; i++){
				stringarray2[i] = stringarray1[i];
			}

			quicksort(&stringarray2, num_ints, sizeof(char*), str_cmp);
			for(int i = 0; i < num_ints; i++){
                                printf("Doubles comming out of the array: %s\n", stringarray2[i]);
                         }
			
		}
		*/		
	}

    return EXIT_SUCCESS;
}
