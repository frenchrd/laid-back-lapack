#include <stdlib.h>
#include <stdio.h>
#include "math.h"
#include "lb_vector.h"
#include "mpi.h"

#define Initialize_Walltimer() double time0 = MPI_Wtime(); double time1;
#define Walltimer_Label(rank_id,msg) time1 = MPI_Wtime(); printf("## [Rank %d] " msg " (%fs)\n",rank_id,time1 - time0); time0 = time1;

double f1_function(double x) {
	return sin(x);
}

double f2_function(double x) {
	return cos(x);
}

typedef struct p_description {
	unsigned int global_length;
	unsigned int local_length;
	int num_ranks;
	int my_rank_id;
	int lower_bound;
} ProblemDescription;

void calculate_lower_bound(ProblemDescription* p) {
	p->lower_bound = p->my_rank_id * p->local_length;
	int leftover = p->global_length % p->num_ranks;
	if (leftover > 0) {
		// Lower ranks have 1 more unit than higher ranks
		if (p->my_rank_id >= leftover) {
			p->lower_bound += leftover;
		}
	}
}	

ProblemDescription specify_p_from_environment(int argc, char** argv) {
	ProblemDescription p;
	if (argc > 1) {
		p.global_length = 1024 * 1024 * atoi(argv[1]);
	} else {
		p.global_length = 1024 * 1024 * 1;
	}
	MPI_Comm_rank(MPI_COMM_WORLD, &(p.my_rank_id));
	MPI_Comm_size(MPI_COMM_WORLD, &(p.num_ranks));
	
	p.local_length = p.global_length / p.num_ranks;
	
	// There may be a bit left over, in which case add one
	// more element to the first few ranks until we've spread
	// the leftover evenly
	if (p.my_rank_id < p.global_length % p.num_ranks) {
		p.local_length += 1;
	}

	calculate_lower_bound(&p);

	return p;
}

int main(int argc, char** argv) {
	MPI_Init(&argc, &argv);

	ProblemDescription p = specify_p_from_environment(argc,argv);
	Initialize_Walltimer();

	

	double local_dot_product;
	int i;
	double h = (double)(2.0 * M_PI / (double)p.global_length);
	Vector f1 = lb_allocate_vector(p.local_length);
	Vector f2 = lb_allocate_vector(p.local_length);
	Vector f1_dot_f2 = lb_allocate_vector(p.local_length);
	Walltimer_Label(p.my_rank_id, "Allocating giant arrays");

	#pragma omp parallel for private(i)
	for(i = 0; i < f1.length; i++) {
		f1.data[i] = f1_function(h * (i+p.lower_bound));
	}
	Walltimer_Label(p.my_rank_id, "Create f1");

	#pragma omp parallel for private(i)
	for(i = 0; i < f2.length; i++) {
		f2.data[i] = f2_function(h * (i+p.lower_bound));
	}
	Walltimer_Label(p.my_rank_id, "Create f2");

	// f1 dot f2
	double dot_product_son;
	lbdp(f1,f2,&local_dot_product);
	MPI_Reduce(&local_dot_product,&dot_product_son,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
	Walltimer_Label(p.my_rank_id, "f1 dot f2");
	
	// norm of f1
	double norm_f1;
	double local_norm;
	lbdp(f1,f1,&local_norm);
	MPI_Reduce(&local_norm,&norm_f1,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
	if (p.my_rank_id == 0) norm_f1 = sqrt(norm_f1);
	Walltimer_Label(p.my_rank_id, "Norm of f1");
	
	// norm of f2
	double norm_f2;
	lbdp(f2,f2,&local_norm);
	MPI_Reduce(&local_norm,&norm_f2,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
	if (p.my_rank_id == 0) norm_f2 = sqrt(norm_f2);
	Walltimer_Label(p.my_rank_id, "Norm of f2");

	MPI_Barrier(MPI_COMM_WORLD);
	if (p.my_rank_id == 0) {
		double theta = acos(dot_product_son / (norm_f1 * norm_f2));
		printf("The dot product of f1 and f2 is %f\n",dot_product_son);
		printf("The angle between f1 and f2 is %f\n",theta);
	}	
	MPI_Finalize();
	return 0;
}
