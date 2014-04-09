/* Example code for Software Systems at Olin College.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    double **data;
    int rows, cols;
} Matrix;


// Makes a new matrix and sets all elements to zero.
Matrix *make_matrix(int rows, int cols) {
    int i;
    Matrix *matrix = malloc(sizeof(Matrix));

    matrix->data = malloc(rows * sizeof(double *));
    matrix->rows = rows;
    matrix->cols = cols;

    for (i=0; i<rows; i++) {
	// use calloc to initialize to 0
	matrix->data[i] = calloc(cols, sizeof(double));
    }
    return matrix;
}

// Prints the elements of a matrix.
void print_matrix(Matrix *matrix) {
    int i, j;

    for (i=0; i<matrix->rows; i++) {
	for (j=0; j<matrix->cols; j++) {
	    printf("%lf ", matrix->data[i][j]);
	}
	printf("\n");
    }
}

// Adds a scalar to all elements of a matrix.
void increment_matrix(Matrix *matrix, int incr) {
    int i, j;

    for (i=0; i<matrix->rows; i++) {
	for (j=0; j<matrix->cols; j++) {
	    matrix->data[i][j] += incr;
	}
    }
}

// Sets the elements of a matrix to consecutive numbers.
void consecutive_matrix(Matrix *matrix) {
    int i, j;

    for (i=0; i<matrix->rows; i++) {
	for (j=0; j<matrix->cols; j++) {
	    matrix->data[i][j] = i * matrix->cols + j;
	}
    }
}

// Sets the elements of a matrix to consecutive numbers.
void magic_square(Matrix *matrix) {
	matrix->data[0][0] = 2;
	matrix->data[0][1] = 7;
	matrix->data[0][2] = 6;
	matrix->data[1][0] = 9;
	matrix->data[1][1] = 5;
	matrix->data[1][2] = 1;
	matrix->data[2][0] = 4;
	matrix->data[2][1] = 3;
	matrix->data[2][2] = 8;
}

// Adds two matrices elementwise and stores the result in the given
// destination matrix (C).
void add_matrix(Matrix *A, Matrix *B, Matrix *C) {
    int i, j;

    assert(A->rows == B->rows && B->rows == C->rows);
    assert(A->cols == B->cols && B->cols == C->cols);

    for (i=0; i<A->rows; i++) {
	for (j=0; j<A->cols; j++) {
	    C->data[i][j] =  A->data[i][j] + B->data[i][j];
	}
    }
}

// Adds two matrices elementwise and returns a new matrix.
Matrix *add_matrix_func(Matrix *A, Matrix *B) {
    Matrix *C = make_matrix(A->rows, A->cols);
    add_matrix(A, B, C);
    return C;
}

// Performs matrix multiplication and stores the result in the given
// destination matrix (C).
void mult_matrix(Matrix *A, Matrix *B, Matrix *C) {
    int i, j, k;

    assert(A->rows == B->cols);
    assert(A->rows == C->rows);
    assert(B->cols == C->cols);

    for (i=0; i<C->rows; i++) {
	for (j=0; j<C->cols; j++) {
	    for (k=0; k<A->cols; k++) {
		C->data[i][j] += A->data[i][k] * B->data[k][j];
	    }
	}
    }
}

// Performs matrix multiplication and returns a new matrix.
Matrix *mult_matrix_func(Matrix *A, Matrix *B) {
    Matrix *C = make_matrix(A->rows, B->cols);
    mult_matrix(A, B, C);
    return C;
}

double matrix_sum1(Matrix *A) {
    double total = 0.0;
    int i, j;

    for (i=0; i<A->rows; i++) {
	for (j=0; j<A->cols; j++) {
	    total += A->data[i][j];
	}
    }
    return total;
}
    
double matrix_sum2(Matrix *A) {
    double total = 0.0;
    int i, j;

    for (j=0; j<A->cols; j++) {
	for (i=0; i<A->rows; i++) {
	    total += A->data[i][j];
	}
    }
    return total;
}
    

// Adds up the rows of A and returns a heap-allocated array of doubles.
double *row_sum(Matrix *A) {
    double total;
    int i, j;

    double *res = malloc(A->rows * sizeof(double));

    for (i=0; i<A->rows; i++) {
	total = 0.0;
	for (j=0; j<A->cols; j++) {
	    total += A->data[i][j];
	}
	res[i] = total;
    }
    return res;
}

// Adds up the columns of A and returns a heap-allocated array of doubles.
double *col_sum(Matrix *A) {
    double total;
    int i, j;

    double *res = malloc(A->cols * sizeof(double));

    for (i=0; i<A->cols; i++) {
	total = 0.0;
	for (j=0; j<A->rows; j++) {
	    total += A->data[j][i];
	}
	res[i] = total;
    }
    return res;
}

// Adds up the diagonals of A and returns a heap-allocated array of doubles.
double *diag_sum(Matrix *A) {
	assert(A->cols == A->rows);
    double total;
    int i, j;
    double *res = malloc(2 * sizeof(double));
    int width = A->cols;
	total = 0.0;
    for (i=0; i<A->cols; i++) {
		total += A->data[i][i];
    }
    res[0] = total;
    total = 0.0;
	for (j=0; j<A->cols; j++) {
    	int width = A->cols;
		total += A->data[j][(width-1)-j];
    }
    res[1] = total;
    return res;
}

// Takes a matrix A and returns an int, 1 if the matrix is a magic square, 
// and 0 otherwise.
int is_magic_square(Matrix *A) {
	int i;
	if (A->cols != A->rows){
		return 0;
	}
    double *row_sums = row_sum(A);
    for (i=0; i<(A->rows)-1; i++) {
    	if (row_sums[i] != row_sums[i+1]) {
    		return 0;
    	}
    }
    double *col_sums = col_sum(A);
    for (i=0; i<(A->cols)-1; i++) {
    	if (col_sums[i] != col_sums[i+1]) {
    		return 0;
    	}
    }
    double *diag_sums = diag_sum(A);
    if (diag_sums[0] != diag_sums[1]) {
    		return 0;
    }
	return 1;
}

int main() {
    int i;

    Matrix *A = make_matrix(3, 4);
    consecutive_matrix(A);
    printf("A\n");
    print_matrix(A);

    Matrix *C = add_matrix_func(A, A);
    printf("A + A\n");
    print_matrix(C);

    Matrix *B = make_matrix(4, 3);
    increment_matrix(B, 1);
    printf("B\n");
    print_matrix(B);

    Matrix *D = mult_matrix_func(A, B);
    printf("D\n");
    print_matrix(D);
    
    Matrix *E = make_matrix(3, 3);
	magic_square(E);
    printf("E\n");
    print_matrix(E);

    double sum = matrix_sum1(A);
    printf("sum = %lf\n", sum);

    sum = matrix_sum2(A);
    printf("sum = %lf\n", sum);

    double *row_sums = row_sum(A);
    for (i=0; i<A->rows; i++) {
		printf("row %d\t%lf\n", i, row_sums[i]);
    }
    // should print 6, 22, 38
    
    i = is_magic_square(D);
    printf("Is D a magic square: %d\n", i);
    //should print 0
    
    i = is_magic_square(E);
    printf("Is E a magic square: %d\n", i);
	//should print 1

    return 0;
}
