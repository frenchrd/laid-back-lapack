#include <stdlib.h>
#include <stdio.h>
#include "math.h"
#include "lb_vector.h"
#include "mpi.h"

#define Initialize_Walltimer() double time0 = MPI_Wtime(); double time1;
#define Increment_Walltimer() time1 = MPI_Wtime(); printf("\t%f seconds\n", time1 - time0); time0 = time1;
#define Walltimer_Label(msg) printf("## " msg "\n");

int main(int argc, char** argv) {
	MPI_Init(&argc, &argv);

	Initialize_Walltimer();
	unsigned int length = 1024l * 1024l * atoi(argv[1]);

	Walltimer_Label("Allocating giant arrays");
	Scalar h = (Scalar)(2.0 * 3.1415 / (Scalar)length);
	Scalar one;
	Scalar two = 2.0;
	int i;
	Vector sin_squared = lb_allocate_vector(length);
	Vector cos_squared = lb_allocate_vector(length);
	Vector sin2pluscos2 = lb_allocate_vector(length);
	Increment_Walltimer();

	Walltimer_Label("Create sin_squared");
	#pragma omp parallel for private(i)
	for(i = 0; i < sin_squared.length; i++) {
		sin_squared.data[i] = (Scalar)pow(sin(h * i),2);
	}
	Increment_Walltimer();

	Walltimer_Label("Create cos_squared");
	#pragma omp parallel for private(i)
	for(i = 0; i < cos_squared.length; i++) {
		cos_squared.data[i] = (Scalar)pow(cos(h * i),2);
	}
	Increment_Walltimer();

	Walltimer_Label("Dot Product");
	lbdp(sin_squared,cos_squared,&one);
	Increment_Walltimer();

	Walltimer_Label("Vector Addition");
	lbvpv(sin_squared, cos_squared, sin2pluscos2);
	Increment_Walltimer();

	Walltimer_Label("Scalar Multiplication");
	lbstv(two, sin2pluscos2, sin2pluscos2);
	Increment_Walltimer();

	Walltimer_Label("Average Vector Components");
	Scalar vector_sum = 0.0;
	#pragma omp parallel for private(i) reduction(+:vector_sum)
	for(i = 0; i < length; i++) vector_sum += sin2pluscos2.data[i];
	Scalar average = vector_sum / h;
	Increment_Walltimer();

	printf("Sin^2 \\dot Cos^2 = %f\n",one);
	MPI_Finalize();
	return 0;
}
