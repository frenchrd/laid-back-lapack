#include <stdlib.h>
#include <stdio.h>
#include "math.h"
#include "lb_vector.h"
#include "mpi.h"

#define Initialize_Walltimer() double time0 = MPI_Wtime(); double time1;
#define Walltimer_Label(msg) time1 = MPI_Wtime(); printf("## [Rank %d] " msg " (%fs)\n",rank_id,time1 - time0); time0 = time1;

Scalar f1_function(Scalar x) {
	return sin(x);
}

Scalar f2_function(Scalar x) {
	return cos(x);
}

int main(int argc, char** argv) {
	MPI_Init(&argc, &argv);
	int rank_id, num_ranks;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank_id);
	MPI_Comm_size(MPI_COMM_WORLD, &num_ranks);

	Initialize_Walltimer();
	unsigned int length = 1024l * 1024l * atoi(argv[1]);
	unsigned int global_length = length * num_ranks;

	Scalar local_dot_product;
	int i;
	Scalar h = (Scalar)(2.0 * M_PI / (Scalar)global_length);
	Vector f1 = lb_allocate_vector(length);
	Vector f2 = lb_allocate_vector(length);
	Vector f1_dot_f2 = lb_allocate_vector(length);
	Walltimer_Label("Allocating giant arrays");

	int lower_bound = rank_id * length;

	#pragma omp parallel for private(i)
	for(i = 0; i < f1.length; i++) {
		f1.data[i] = f1_function(h * (i+lower_bound));
	}
	Walltimer_Label("Create f1");

	#pragma omp parallel for private(i)
	for(i = 0; i < f2.length; i++) {
		f2.data[i] = f2_function(h * (i+lower_bound));
	}
	Walltimer_Label("Create f2");

	lbdp(f1,f2,&local_dot_product);
	Walltimer_Label("Dot Product");

	Scalar dot_product_son;

	MPI_Datatype typeOfScalar;
	#ifdef LB_SCALAR_DOUBLE
		typeOfScalar = MPI_DOUBLE;
	#else
		typeOfScalar = MPI_FLOAT;
	#endif

	MPI_Reduce(&local_dot_product,&dot_product_son,1,typeOfScalar,MPI_SUM,0,MPI_COMM_WORLD);
	Walltimer_Label("Reduction");

	Scalar angle = asin(dot_product_son);
	if (rank_id == 0) {
		printf("The dot product of f1 and f2 is %f\n",dot_product_son);
		printf("The angle between f1 and f2 is %f\n",angle);
	}	
	MPI_Finalize();
	return 0;
}
