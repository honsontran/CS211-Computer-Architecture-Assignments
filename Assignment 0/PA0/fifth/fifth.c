#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//declare functions
int magic(int size, int matrix[size][size]);
int checkDuplicate(int arr[], int number, int size);

int main(int argc, char* argv[]) {

	char line[100];
	int numbers[100];
	char delimit[2] = " \t";		//token divider
	char * token;
	int size;

  	//input file name
	char * file = argv[1];
    FILE *fp = fopen(file, "r");	// open the file to "r" --> read

    //Figure out the size of square matrix
    fscanf(fp, "%d", &size);

	//Create the matrix
	int matrix[size][size];

	fgets(line, 30, fp);	//reposition pointer to 2nd line

	//Now, input data into the matrices
	//by tokenizing each row.
	int j = 0;
	int i = 0;
	int number = 0;
	for (; i < size; i++) {	//iterating per line

		fscanf(fp, "%[^\n]\n", line);	//get the line		
		token = (char*)strtok(line, delimit);
		
		int k = 1;
		for(; k <= size; k++) {			
			
			if (token != NULL) {
				
				number = atoi(token);
				if (checkDuplicate(numbers, number, size)) {
					printf("not-magic\n");
					return 0;
				}

				else numbers[j] = number;
			}

			token = (char*)strtok(NULL, delimit);
			j++;				
		}
	}

	//Loop through numbers[] and put into matrices
	int counter = 0;
	int loopI = 0;
	for (; loopI < size; loopI++) {
		
		int j = 0;
		for(; j < size; j++) {
			matrix[loopI][j] = numbers[counter];

			counter++;
		}
	}

	/*
	//toString
	for (int i = 0; i < size; i++) {
        
        for (j = 0; j < size; j++) {
	        printf("%d ", matrix[i][j]);
	    }
	        printf("\n");

    }
    */

    //Check if magic
    int isMagic = magic(size, matrix);

    //return desired output
    if (isMagic) {
    	printf("magic\n");
    }

    else{
    	printf("not-magic\n");
    }

    return 0;
}

/*
 * Checks the array if there is a duplicate
 */
int checkDuplicate(int arr[], int number, int size) {

	int i = 0;
	for(; i < size; i++) {

		//match found
		if (arr[i] == number) return 1;
	}

	return 0;
}
/*
 * Checks all diagonals, rows, and columns
 * returns a boolean as int (1 if magic)
 */ 
int magic(int size, int matrix[size][size]) {
	
	int magicSum = 0;

	int sumRow = 0;
	int sumCol = 0;
	int sumDiag1 = 0;
	int sumDiag2 = 0;

	//Grab a sum
	int col = 0;
	for(; col < size; col++) {
		magicSum += matrix[0][col];
	}

	//Test rows & cols & diagonals
	int row = 0;
	for(; row < size; row++) {
		
		int col = 0;
		for(; col < size; col++) {
			
			sumRow += matrix[row][col];
			sumCol += matrix[col][row];

			//This adds up the diagonals
			if (row == col) {
				sumDiag1 += matrix[row][col];
				sumDiag2 += matrix[row][size-1-row];
			}
		}

		//Check if sum is magic
		if ( (sumRow != magicSum) && (sumCol != magicSum) ) {
			//printf("sumRow: %d | sumCol: %d\n", sumRow, sumCol);
			return 0;
		}

		//Reset row and col for next iteration
		sumRow = 0;
		sumCol = 0;
	}

	//Check the diagonals after adding
	if ( (sumDiag1 != magicSum) && (sumDiag2 != magicSum) ) {
		return 0;
	}

	return 1;		//return if all sums are same
}