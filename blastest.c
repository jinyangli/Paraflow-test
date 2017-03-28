#include <stdlib.h>
#include <stdio.h>
#include <gsl/gsl_cblas.h>
#include <strings.h>
#include <assert.h>
#include <time.h>

void
init_rand_matrix(float *mat, int size)
{
	for (int i = 0; i < size; i++) {
		mat[i] = (float)rand()/(float)(RAND_MAX);
	}
}

void
main (int argc, char **argv)
{
	int n = 8000;
	if (argc > 1) {
		n = atoi(argv[1]);
	}
	printf("Matrix multiply two %d x %d matrixes\n", n, n);

	int lda = 3;

	float *matA = malloc(sizeof(float)*n*n);
	init_rand_matrix(matA, n*n);

	float *matB = malloc(sizeof(float)*n*n);
	init_rand_matrix(matB, n*n);

	float *matC = malloc(sizeof(float)*n*n);
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
}

