#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {

	int arrLength;
	char line[50];

  	//input file name
	char * file = argv[1];
    FILE *fp = fopen(file, "r");	// open the file to "r" --> read

    //Find out the length of the array
    fscanf(fp, "%d", &arrLength);
    
    //Debug: Array length
    //printf("The length is: %d\n", arrLength);

    //initialize array
 	int arr[arrLength];

 	//tokenize the string from the next line in file.
 	int forI = 0;
 	for (; forI < arrLength; forI++) {
 		
 		fscanf(fp, "%s", line);
 		//printf("\nOur line is: %s\n", line);

 		arr[forI] = atoi(line);
 	}
 	
 	/*
 	//Debug
 	printf("\n--------------------------------------------------\n");
 	printf("\nUnsorted:\n");

 	//toString
	for(int i = 0; i < 5; i++) {
		printf("%d\t ", arr[i]);
	}
 	printf("\n--------------------------------------------------\n");
	*/

	//insertion sort
	int forJ = 1;
	for (; forJ < arrLength; forJ++) {

		int curr = arr[forJ];
		int j = forJ-1;
		
		while (j >= 0 && arr[j] > curr) {
           arr[j+1] = arr[j];
           j = j-1;
		}

       arr[j+1] = curr;
	}

	//toString
	int k = 0;
	int arrSize = sizeof(arr)/sizeof(arr[0]);
	for(; k < arrSize; k++) {
		printf("%d\t", arr[k]);
	}

	fclose(fp);

	return 0;
}
