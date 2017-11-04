#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
//declare functions
void multiply(int size, int mat1[size][size],
    int mat2[size][size],int ans[size][size]);
 
int main(int argc, char* argv[]) {
   
    //To be used with strok()
    int numbers[50];            //place ints after strtok()
    char delimit[2] = " \t";        //token divider
    char line[100];             //read rows from file
    memset(line, '\0', 100);
    char * token;           //determine when to stop tokening
 
    int size;       //size of matrix
    int power;      //how many times to multiply

    //input file name
    char * file = argv[1];
    FILE *fp = fopen(file, "r");    // open the file to "r" --> read

    //Find the power at end of file.
    while ( !feof(fp) ) {
        fscanf(fp, "%d", &power);
    }
    //printf("\nPower: %d\n", power);
 
    rewind(fp);     //start at beginning of file
 
    //Figure out the size of square matrix
    fscanf(fp, "%d", &size);
    //printf("Size: %d\n", size);
 
    fgets(line, 30, fp);    //reposition pointer to 2nd line
 
    //Now, input data into the matrices
    //by tokenizing each row.
    int j = 0;
    int i = 0;
    for (; i < size; i++) { //iterating per line
 
        fscanf(fp, "%[^\n]\n", line);   //get the line
        //printf("\nCurrent line: %s\n", line);
         
        token = (char*)strtok(line, delimit);
        //printf("\nTokened: %s\n", token);
        int k = 1;
        for(; k <= size; k++) {
             
            if (token != NULL) {numbers[j] = atoi(token);}
 
            //printf("\nInserted: %s ---> numbers[%d]", token, j);
            //printf("\nConfirm: %d\n", numbers[j]);
 
            token = (char*)strtok(NULL, delimit);
            j++;
            //printf("\nTokened: %s\nIteration: %d", token, j);                   
        }
    }
 
    /*
     *ALGORITHM TO START MULTIPLYING MATRICES
     */
 
    //Now we can create the matrices for algorithm
    int matrix1[size][size];    //iteration matrix
    int ans[size][size];        //holds answer
    int original[size][size];   //ONLY holds M^1
 
  
    //Loop through numbers[] and put into matrices
    int counter = 0;
    int forI = 0;
    for (; forI < size; forI++) {
        
        int j = 0;
        for(; j < size; j++) {
            matrix1[forI][j] = numbers[counter];
            original[forI][j] = numbers[counter];
 
            counter++;
        }
    }
 
    //Multiply matrix by itself according to power.
    int currPwr = 0;
    for(; currPwr < power-1; currPwr++) {
         
        //Make sure ans is 0 at start of iteration
        int i = 0;
        for (; i < size; i++) {        
            
            int j = 0;
            for (; j < size; j++) {
                ans[i][j] = 0;
            }
        }   //end reset ans matrix
 
        //Multiply the matrices and put them to ans.
        multiply(size, matrix1, original, ans);
 
        //Now, put the ans into matrix1, clear ans.
        //to prepare for next iteration
        int forI = 0;
        for (; forI < size; forI++) {        
            
            int j = 0;
            for (; j < size; j++) {
                matrix1[forI][j] = ans[forI][j];
            }
        }   //end copying answer
     }   //end power loop
 
    //toString()
    //printf("\nAns is \n");
    int stringI = 0;
    for (; stringI < size; stringI++) {
        
        int j = 0; 
        for (; j < size; j++) {
            printf("%d\t", ans[stringI][j]);
        }
            printf("\n");
 
    }
 
    return 0;
}
 
// This function multiplies mat1[][] and mat2[][],
// and stores the result in ans[][]
void multiply(int size, int mat1[size][size],
    int mat2[size][size],int ans[size][size]) {
 
    int i, j, k;
    //Matrix multiplication
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++) {
            
            for (k = 0; k < size; k++)
                ans[i][j] += mat1[i][k]*mat2[k][j];
        }
    }
}