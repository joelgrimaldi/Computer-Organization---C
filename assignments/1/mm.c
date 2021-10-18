/*********************************************************************************/
/* CSCI-2500 Assignment 1: 2-D/ NxN Matrix Swap and  Multiplication **************/
/* Name: Joel Grimaldi *****************************************************/
/*********************************************************************************/

/*********************************************************************************/
/* Usual suspects to include *****************************************************/
/*********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>

/*********************************************************************************/
/* Function Calls ****************************************************************/
/*********************************************************************************/

double **mm_alloc( int size )
{
    /*
     * hints: allocate an array of pointers to a double, 
     * then allocate an row/array of doubles and assign each double pointer that row
     * use calloc for allocation and zeroing out all the bytes
     */

    double **arr = (double **)calloc(size, sizeof(double*));
    for(int i = 0; i < size; i++){
        arr[i] = (double*)calloc(size, sizeof(double));
    }

    return(arr);
}

void mm_free( int size, double **matrix  )
{
    /*
     * hint: reverse of the allocation process 
     * by freeing each array of doubles, 
     * then free the array of double pointers
     */

    for(int i = 0; i < size; i++){
        free(matrix[i]);
    }
    free(matrix);

    return;
}

double **mm_read( char *filename, int *size ) 
{
    /*
    * hints: fopen the file, then use fgets or getline to read each line of data.
    * The first line is the size of the matrix, so read it first. 
    * make sure you record the "size" in the size argument.
    * Next alloc each of the matrixes.
    * Use sscanf to take the line of text and parse out the matrix entry.
    */

    double **matrix = NULL;
    
    FILE *fp = fopen(filename, "r"); //open for reading
    char str[128];
    unsigned long size_t = 128;

    if(fp == NULL){
        perror("Error opening file");
        exit(-1);
    }

    fgets(str, size_t, fp);

    double d;
    *size = atoi(str);

    matrix = mm_alloc(*size);

    for(int i = 0; i < *size; i++){
        for(int j = 0; j < *size; j++){
            fgets(str, size_t, fp);         //gets next char* in file
            sscanf(str, "%lf", &d);         //transforms char* into double
            matrix[i][j] = d;               //puts in matrix
        }
    }

    fclose(fp);
        
    return( matrix );
}

void mm_print( int size, double **matrix )
{
    /*
     * iterate over the matrix entries across each row.
     * when a row is complete insert a newline character "\n"
     */
    printf("/******** START of 2-D Matrix ****************************************************************************\n");

    for(int i = 0; i < size; i++){          //basic double array print loop
        for(int j = 0; j < size; j++){
            printf("%lf\t", matrix[i][j]);
        }
        printf("\n");
    }

    printf("/******** END of 2-D Matrix ******************************************************************************\n");

    return;
}

double **mm_swap( int size, double **matrix )
{
    /*
        * hints: allocate space for swapped matrix
        * compute swap matrix using original matrix as input. 
    */

    double **swap = NULL;
    swap = mm_alloc(size);

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){      //allocate and fill swap with the contents of matrix
            swap[i][j] = matrix[i][j];
        }
    }

    double temp;

    for(int i = 0; i < size; i++){          //rows
        for(int j = 0; j < size-2; j++){    //columns minus 2
            temp = swap[i][j];                  //save spot 1 in temp

            swap[i][j] = swap[i][j+2];          //take spot 3 and put it in spot one
            swap[i][j+2] = temp;                //take temp(spot 1) and put it in spot 3
        }
    }

    return( swap );
}

double **mm_matrix_mult( int size, double **matrix, double **transpose )
{
    /*
     * hints: alloc a results matrix, 
     * do the matrix multiple per the quad loop method.
     * this is an extension of regular 2-D matrix mult. 
     * return the results_matrix
     */

    double **ret = NULL;
    ret = mm_alloc(size);

    int sum;

    for(int i = 0; i < size; i++){      //row
        for(int j = 0; j < size; j++){  //column
            sum = 0;
            for(int k = 0; k < size; k++){  //shared variable
                sum+=(matrix[i][k]*transpose[k][j]);
            }
            ret[i][j] = sum;
        }
    }

    return( ret );
}

int main()
{
    /*
     * you must keep this function AS IS. 
     * you cannot modify it!
     */
    char filename[256];
    double **matrix=NULL;
    double **swap_matrix=NULL;
    double **results_matrix=NULL;
    int size=0;

    printf("Please enter the matrix data file name: ");
    scanf( "%s", filename );
    printf("\n");

    matrix = mm_read( filename, &size );
    swap_matrix = mm_swap( size, matrix ); 
    results_matrix = mm_matrix_mult( size, matrix, swap_matrix );

    printf("Output of Swap Matrix\n");
    mm_print( size, swap_matrix );
    mm_print( size, results_matrix );
    mm_free( size, matrix );
    mm_free( size, swap_matrix );
    mm_free( size, results_matrix );
    return( 0 ); 
}
