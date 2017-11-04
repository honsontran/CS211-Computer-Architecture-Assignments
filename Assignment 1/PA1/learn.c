#include "learn.h"

int main(int argc, char* argv[]) {

	int i, j, k;

	/*
	 *	TRAIN FILE PARSING
	 */
	
	//input the training file
	char* trainFile = argv[1];

	//Open the file and determine parameters
	FILE * fp = fopen(trainFile, "r");

	//Read first line for number of attributes
	int attributes;
	fscanf(fp, "%d", &attributes);
	attributes++;		//add in base price attribute

	//Read second line for number of samples
	int samples;
	fscanf(fp, "%d", &samples);

	/*
	 * TOKENIZING AND PARSING THE TRAIN MATRIX
	 */
	
	//Initialize arrays to heap
	double** attributeArr = malloc( samples * sizeof(*attributeArr) );
	for (i = 0; i < samples; i++) {
		attributeArr[i] = malloc( attributes * sizeof(*attributeArr[i]) );
	}
	
	double** price = malloc(samples * sizeof(*price) );
	for (i = 0; i < samples; i++) {
		price[i] = malloc( 1 * sizeof(*price[i]) );
	}

	char line[100];
	fgets(line, 100, fp);	//Bug: put here to skip \n
	char * token;			//stores each entry
	char * string;
	
	j = 1;
	for (i = 0; i < samples; i++) {

		fgets(line, 100, fp);	//get first line
		string = strdup(line);	//redundant but works with strsep()

		//Create the column of 1's for base price
		attributeArr[i][0] = 1;

		//Continue parsing the rest of the matrix
		while ( (token = strsep(&string, ",")) != NULL ) {

			//Check if we have to insert to price column
			if (j == attributes) {
				price[i][0] = atof(token);
				j = 1; 		//reset for next iteration
			}

			//If not, put into attributes matrix
			else {
				attributeArr[i][j] = atof(token);
				j++;	
			}
		}	//ends token loop
	}	//end looping through lines/samples
		free(string);
		free(token);
		fclose(fp);

	/*
	 *	TEST FILE PARSING
	 */

	//input the test file
	char * testFile = argv[2];

	//Open the file and determine parameters
	FILE * fp2 = fopen(testFile, "r");

	//Read first line for number of test samples
	int testSamples;
	int testAttributes = attributes-1;
	fscanf(fp2, "%d", &testSamples);

	/*
	 * TOKENIZING AND PARSING THE TEST MATRIX
	 */
	double testMatrix[testSamples][attributes];

	fgets(line, 100, fp2);		//Bug: put here to skip \n

	for (i = 0; i < testSamples; i++) {

		fgets(line, 100, fp2);		//get first line
		string = strdup(line);		//redundant but works with strsep()

		testMatrix[i][0] = 1;		//set to 1 for base price attribute column

		for (j = 1; j < attributes; j++) {

			token = strsep(&string, ",");
			
			//Insert into the matrix
			testMatrix[i][j] = atof(token);

		}

	} //end test matrix parsing loop 
	fclose(fp2);

	/*
	 * MACHINE LEARNING: CALCULATING WEIGHTS
	 *		X = attributeArr
	 * 		Y = price array
	 * 		Weight = (X^T * X)^-1 * X^T * Y
	*/

	//1) Transpose attributeArr
	double** transposed = calloc( attributes, sizeof(*transposed) );
	for (i = 0; i < attributes; i++) {
		transposed[i] = calloc( samples, sizeof(*transposed[i]) );
	}
	transpose(samples, attributes, attributeArr, transposed);

	//2) multiple transposed w/ attributeArr to become square matrix
	double** multiplied = calloc( attributes, sizeof(*multiplied) );
	for (i = 0; i < attributes; i++) {
		multiplied[i] = calloc( attributes, sizeof(*multiplied[i]) );
	}

	//Multiply
    for (i = 0; i < attributes; i++)
    {
        for (j = 0; j < attributes; j++) {
            
            for (k = 0; k < samples; k++)
                multiplied[i][j] += transposed[i][k]*attributeArr[k][j];
       		
        }
    }

	/* 3) Find the inverse of multiplied
	*/

	//Initialize the identity matrix on the heap
	double** identity;
	identity = calloc( samples, sizeof(*identity) );
	for (i = 0; i < samples; i++) {
		identity[i] = calloc( samples, sizeof(*identity[i]) );
	}

	//create the diagonal of 1s
	createIdentity(samples, identity);

	//Augment attributeArr for guass-jordan elimination
	double** augmented = calloc( attributes, sizeof(*augmented) );
	for (i = 0; i < attributes; i++) {
		augmented[i] = calloc( 2*attributes, sizeof(*augmented[i]) );
	}

	for (i = 0; i < attributes; i++) {
		for (j = 0; j < attributes; j++) {
			
			//A) Place matrix A to left of augment
			augmented[i][j] = multiplied[i][j];

			/* B) Place inverse to right of augment.
			 * Augment's indices are the [0] index for identity.
			 * It's in the same row, but size+j column.
			 */
			augmented[i][attributes+j] = identity[i][j];
		}
	}

	//Now, we can free identity and multiplied
	for (i = 0; i < samples; i++) {
		free(identity[i]);
	}
	free(identity);

	for (i = 0; i < attributes; i++) {
		free(multiplied[i]);
	}
	free(multiplied);
	
	//Find the inverse via Gauss-Jordan elimination
	gaussian(attributes, attributes*2, augmented);

	//Get the inverse from previous function
	double** inverse = calloc( attributes, sizeof(*inverse) );
	for (i = 0; i < attributes; i++) {
		inverse[i] = calloc( attributes, sizeof(*inverse[i]) );
	}

	getInverse(attributes, augmented, inverse);

	//We can now free augmented
	for (i = 0; i < attributes; i++) {
		free(augmented[i]);
	}
	free(augmented);


	//Multiply this by the transpose again
	double** multiplied2 = calloc( attributes, sizeof(*multiplied2) );
	for ( i = 0; i < attributes; i++) {
		multiplied2[i] = calloc( samples, sizeof(*multiplied2[i]) );

	}

	//Multiply
    for (i = 0; i < attributes; i++)
    {
        for (j = 0; j < samples; j++) {
            
            for (k = 0; k < attributes; k++) {       
                multiplied2[i][j] += inverse[i][k] * transposed[k][j];
            }

        }
    }

    //We can now free inverse and transposed
    for (i = 0; i < attributes; i++) {
    	free(inverse[i]);
    	free(transposed[i]);
    }
    free(inverse);
    free(transposed);

    //Finally, multiply this by the price array to find weight
    double** weight = malloc( attributes * sizeof(*weight) );
    for (i = 0; i < attributes; i++) {
    	weight[i] = malloc( 1 * sizeof(*weight[i]) );
    	weight[i][0] = 0;
    }

    //Multiply
    for (i = 0; i < attributes; i++)
    {
        for (j = 0; j < 1; j++) {
            
            for (k = 0; k < samples; k++) {                
                weight[i][j] += multiplied2[i][k] * price[k][j];
            }

        }
    }

    /*
     *	CALCULATING PREDICTED HOUSE PRICES
     *		X = test attributes
     *		W = weight matrix
     *		Y = final price
     *		
     *		Learning formula: X * W = Y
     */

    //Create an array to store these test prices
    double** testPrices = calloc( testSamples, sizeof(*testPrices) );
    for (i = 0; i < testSamples; i++) {
    	testPrices[i] = calloc( 1, sizeof(*testPrices[i]) );
    }

    //Multiply the samples by the weights
    for (i = 0; i < testSamples; i++)
    {
        for (j = 0; j < 1; j++) {
            
            for (k = 0; k < attributes; k++)
                testPrices[i][j] += testMatrix[i][k] * weight[k][j];
        }
    }

    /*
     *	DISPLAYING THE ANSWER
     *		loop through the price array and print them
     */
    for (i = 0; i < testSamples; i++) {
    	printf("%.0f\n", testPrices[i][0]);
    }

    /*
     *	FREEING ALLOCATED MEMORY
     */

    //Free arrays w/ size testSamples
    for (i = 0; i < testSamples; i++) {
		free(testPrices[i]);
	}
	free(testPrices);

	//Free arrays w/ size sample
	for (i = 0; i < samples; i++) {
		free(attributeArr[i]);
		free(price[i]);
	}
	free(attributeArr);
	free(price);

	//Free arrays w/ size attributes
    for (i = 0; i < attributes; i++) {
    	free(multiplied2[i]);
    }
    free(multiplied2);

	return 0;
}
