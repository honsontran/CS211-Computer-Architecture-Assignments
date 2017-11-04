#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Declare functions
void gaussian(int rows, int cols, double** matrix);

void createIdentity(int size, double** identity);

void getInverse(int size, double** augment,
	double** inverse);

void transpose(int row, int col,
  double** matrix, double** transpose);

/* WORKING
 * Input a blank matrix and set the diagonal to 1's
 * to create an identity matrix
 */
void createIdentity(int size, double** identity) {

  //Create the identity
  int i, j;
  for ( i = 0; i < size; i++) {

    for (j = 0; j < size; j++) {
      
      identity[i][j] = 0;  //set to 0
      
      //if on diagonal, set to 1
      if (i == j) identity[i][j] = 1;

    } //end j loop
  } //end i loop
} 

/*
 * Takes the gaussian'd matrix and gives back
 * only the inverse.
 */
void getInverse(int size, double** augment, double** inverse) {

	//Grab the right half of augmented matrix for inverse.
	int i, j;

	for (i = 0; i < size; i++) {
		
		for (j = 0; j < size; j++) {
			inverse[i][j] = augment[i][j+size];
		}

	}
}

/*
 * Transposes a given matrix
 */
void transpose(int row, int col, double** matrix, double** transpose) {
  
  int i, j;

  // Finding the transpose of matrix a
  for(i = 0; i < row; i++) {
    
    for(j = 0; j < col; j++) {
      transpose[j][i] = matrix[i][j];
    }

  }

}


/*
 * Takes in a 2D matrix, creates identity matrix,
 * augments them, and computes the inverse
 * via Gaussian-Jordan Method and returns the
 */
void gaussian(int rows, int cols, double** matrix) {
  
  int r = 0, c = 0, pivotRow = 0, pivotCol = 0;
  int i, j;       //for iteration
  double scalar;
  
  /* Notes - STEP 1: FORWARD ELIMINATION
          (UPPER TRIANGULAR MATRIX)
    pivotCol = keeps track of pivot column
    pivotRow = keeps track of picot row
    c, r = used to increment and manipulate rows & cols
   */
  

  for(c = 0, r = 0; pivotRow < rows; pivotCol++, pivotRow++) {
    /* 1) Create the pivot position by dividing
     * the pivot entry by itself to create 1.
     */
    for(c = cols-1; c >= pivotCol; c--) {
      
      //printf("dividing %0.2f by %0.2f\n", matrix[pivotRow][c], matrix[pivotRow][pivotCol]);
      
      //Iterate through the columns and divide by pivot position
      matrix[pivotRow][c] /= matrix[pivotRow][pivotCol];


    } //end step 1

    /* 2) Perform the row operation based on the pivot
     *    Row operation is as follows:
     *      x = entry that needs to turn to 0
     *    x*R_pivot + R_target --> R_target
     */
    if (pivotRow != rows) {
      for(r = pivotRow+1; r < rows; r++){

        for(c = cols-1; c >= pivotCol; c--) {
          
          //printf("matrix[%d][%d](%.2f) = -%.2f * %.2f + %.2f\n", r, c, matrix[r][c], matrix[r][pivotCol], matrix[pivotRow][c], matrix[r][c] );
          matrix[r][c] = -matrix[r][pivotCol] * matrix[pivotRow][c] + matrix[r][c];
        }

      } //end step 2
    }

  } //end of foward elimination loop


  /* STEP 2: BACKWARD ELIMINATION
     All variables have the same purpose. We now
     run the same algorithm but finish reducing the
     upper triangle.
   */

  //setpivotCol to rows (we only want to 0 out matrix A, not the Identity matrix) 
  pivotCol = rows; pivotRow = rows;

  //Iterate through the matrix, iterating backwards to 0 the upper triangle.
  for(pivotCol--,pivotRow--;pivotCol>0;pivotCol--,pivotRow--){  
  
  //printf("pivotCol: %d | pivotRow: %d\n", pivotCol, pivotRow);    
    for(r = pivotRow-1; r >= 0; r--){
      for(c = pivotCol; c >= pivotCol; c--){

        
        //printf("pivotCol: %d | pivotRow: %d | r: %d | c: %d\n", pivotCol, pivotRow, r, c);

        //printf("Row Operations: \n");
        //printf("matrix[%d][%d] = -(%4.5f * %4.5f) + %4.5f\n",
          //r, c, matrix[r][pivotCol], matrix[pivotRow][c], matrix[r][c]);

        scalar = matrix[r][pivotCol];
        matrix[r][c] = -(scalar * matrix[pivotRow][pivotCol]) + matrix[r][c];
        
        //repeat this operation for the inverse
        int invRow = r;
        for (i = rows; i < cols; i++) {
          
          
          //printf("\nInverse Conducted: \n");
          //printf("matrix[%d][%d] = -(%4.5f * %4.5f) + %4.5f\n\n",
            //invRow, i, scalar, matrix[pivotRow][i], matrix[invRow][i]);
          

          matrix[invRow][i] = -(scalar * matrix[pivotRow][i]) + matrix[invRow][i];
        }
      } //end backwards col iteration
    } //end backwards row iteration
  } //end of backwards elimination
}