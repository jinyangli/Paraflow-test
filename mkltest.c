// this code adapts from Intel MKL's dgemm_example.c 
#define min(x,y) (((x) < (y)) ? (x) : (y))

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <strings.h>
#include "mkl.h"

void
init_rand_matrix(float *mat, int size)
{
	for (int i = 0; i < size; i++) {
		mat[i] = (float)rand()/(float)(RAND_MAX);
	}
}


int main(int argc, char **argv)
{
    int n = 1000;
    if (argc > 1) {
	n = atoi(argv[1]);
    }
    printf("MKL matrix multiply two %d x %d matrixes\n", n, n);

    //allocate memory for matrices aligned on 64-byte boundary
    float *matA = (float *)mkl_malloc( n*n*sizeof( float), 64 );
    float *matB = (float *)mkl_malloc( n*n*sizeof( float), 64 );
    float *matC = (float *)mkl_malloc( n*n*sizeof( float), 64 );
    assert(matA && matB && matC);

    init_rand_matrix(matA, n*n);
    init_rand_matrix(matB, n*n);
    bzero(matC, sizeof(float)*n*n);

    /* Compute C = A B */
    struct timespec start, end;
    assert(clock_gettime( CLOCK_REALTIME, &start)==0);
    cblas_sgemm (CblasRowMajor, 
		    CblasNoTrans, CblasNoTrans, n, n, n,
		    1.0, matA, n, matB, n, 0.0, matC, n);
    assert(clock_gettime( CLOCK_REALTIME, &end)==0);
    double duration = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_nsec-start.tv_nsec)/1000000.0;

    printf("Duration: %2f\n", duration);

    mkl_free(matA);
    mkl_free(matB);
    mkl_free(matC);

    return 0;
}
