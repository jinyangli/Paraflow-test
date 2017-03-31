// this code adapts from Intel MKL's dgemm_example.c 
#define min(x,y) (((x) < (y)) ? (x) : (y))

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <strings.h>
#include <stdbool.h>
#include "mkl.h"

#define MAX_SHARDS 16

void
init_rand_matrix(float *mat, int size)
{
	for (int i = 0; i < size; i++) {
		mat[i] = (float)rand()/(float)(RAND_MAX);
	}
}

void
row_partition(int n)
{
    float *matB = (float *)mkl_malloc( n*n*sizeof( float), 64 );
    assert(matB);
    init_rand_matrix(matB, n*n);

    double durations[MAX_SHARDS+1];
    //each shard of computation calculates
    // C = A * B
    // where A is of dimension (n/i)*n and B is of dimension n*n
    for (int i = 1; i <= MAX_SHARDS; i=2*i) {
	    int sn = n/i;
	    //allocate memory for matrices aligned on 64-byte boundary
	    float *matA = (float *)mkl_malloc( sizeof(float)*sn*n, 64 );
	    float *matC = (float *)mkl_malloc( sizeof( float)*sn*n, 64 );
	    assert(matA && matC);
	    init_rand_matrix(matA, sn*n);
	    bzero(matC, sizeof(float)*sn*n);

	    /* Compute C = A B */
    	    struct timespec start, end;
	    assert(clock_gettime( CLOCK_REALTIME, &start)==0);
	    cblas_sgemm (CblasRowMajor, 
			    CblasNoTrans, CblasNoTrans, sn, n, n,
			    1.0, matA, n, matB, n, 0.0, matC, n);
	    assert(clock_gettime( CLOCK_REALTIME, &end)==0);
	    durations[i] = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_nsec-start.tv_nsec)/1000000.0;

	    mkl_free(matA);
	    mkl_free(matC);
    }

    mkl_free(matB);

    for (int i = 1; i <= MAX_SHARDS; i=i*2) {
	    printf("%d\t", i);
    }
    printf("\n");
    for (int i = 1; i <= MAX_SHARDS; i=i*2) {
	    printf("%.1f\t", durations[i]);
    }
    printf("\n");
    for (int i = 1; i <= MAX_SHARDS; i=i*2) {
	    printf("%.1f\t", durations[1]/durations[i]);
    }
    printf("\n");
}

void
column_partition(int n, bool accum)
{
    float *matC = (float *)mkl_malloc( n*n*sizeof( float), 64 );
    assert(matC);

    double durations[MAX_SHARDS+1];
    for (int i = 1; i <= MAX_SHARDS; i=2*i) {
	    int sn = n/i;
	    //allocate memory for matrices aligned on 64-byte boundary
	    float *matA = (float *)mkl_malloc( sizeof(float)*sn*n, 64 );
	    float *matB = (float *)mkl_malloc( sizeof( float)*n*sn, 64 );
    	    float *tmp = (float *)mkl_malloc( n*n*sizeof( float), 64 );
	    assert(matA && matB && tmp);
	    init_rand_matrix(matA, sn*n);
	    init_rand_matrix(matB, n*sn);
	    bzero(tmp, sizeof(float)*sn*n);

	    /* Compute tmp = A B */
    	    struct timespec start, end;
	    assert(clock_gettime( CLOCK_REALTIME, &start)==0);
	    cblas_sgemm (CblasRowMajor, 
			    CblasNoTrans, CblasNoTrans, n, n, sn,
			    1.0, matA, sn, matB, n, 0.0, tmp, n);
	    if (accum) { 
		    /* Accumulate C += tmp */
		    cblas_saxpy(n*n, 1.0, tmp, 1, matC, 1); 
	    }
	    assert(clock_gettime( CLOCK_REALTIME, &end)==0);
	    durations[i] = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_nsec-start.tv_nsec)/1000000.0;

	    mkl_free(matA);
	    mkl_free(matB);
	    mkl_free(tmp);
    }

    mkl_free(matC);

    for (int i = 1; i <= MAX_SHARDS; i=i*2) {
	    printf("%d\t", i);
    }
    printf("\n");
    for (int i = 1; i <= MAX_SHARDS; i=i*2) {
	    printf("%.1f\t", durations[i]);
    }
    printf("\n");
    for (int i = 1; i <= MAX_SHARDS; i=i*2) {
	    printf("%.1f\t", durations[1]/durations[i]);
    }
    printf("\n");

}

int main(int argc, char **argv)
{
    int n = 1024*8;
    if (argc > 1) {
	n = atoi(argv[1]);
    }
    printf("MKL matrix multiply two %d x %d matrixes\n", n, n);
    printf("----------row partition----------------\n");
    row_partition(n);
    printf("----------column partition (with accumulation)-------------\n");
    column_partition(n, true);
    printf("----------column partition (w/o accumulation)-------------\n");
    column_partition(n, false);
    return 0;
}
