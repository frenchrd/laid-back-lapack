#include <stdlib.h>
#include <stdio.h>
#include "math.h"
#include "lb_vector.h"
#include "mpi.h"

#define Initialize_Walltimer() double time0 = MPI_Wtime(); double time1;
#define Increment_Walltimer() time1 = MPI_Wtime(); printf("%f seconds\n", time1 - time0); time0 = time1;


int main(int argc, char** argv) {
	MPI_Init(&argc, &argv);

	Initialize_Walltimer();
	unsigned int length = atoi(argv[1]);

	printf("Allocating giant arrays: ");
	Scalar h = (Scalar)(2.0 * 3.1415 / (Scalar)length);
	Scalar one;
	int i;
	Vector sin_squared = lb_allocate_vector(1024l * length);
	Vector cos_squared = lb_allocate_vector(1024l * length);
	Increment_Walltimer();

	printf("About to create sin_squared: ");
	#pragma omp parallel for private(i)
	for(i = 0; i < sin_squared.length; i++) {
		sin_squared.data[i] = (Scalar)pow(sin(h * i),2);
	}
	Increment_Walltimer();

	printf("About to create cos_squared: ");
	#pragma omp parallel for private(i)
	for(i = 0; i < cos_squared.length; i++) {
		cos_squared.data[i] = (Scalar)pow(cos(h * i),2);
	}
	Increment_Walltimer();

	printf("About to create dot product: ");
	lbdp(sin_squared,cos_squared,&one);
	Increment_Walltimer();

	printf("Sin^2 + Cos^2 = %f\n",one);
	MPI_Finalize();
	return 0;
}
