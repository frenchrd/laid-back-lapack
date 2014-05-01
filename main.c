#include <stdlib.h>
#include <stdio.h>
#include "math.h"
#include "lb_vector.h"

int main(int argc, char** argv) {
	unsigned int length = atoi(argv[1]);

	printf("Allocating giant arrays\n");
	Scalar h = (Scalar)(2.0 * 3.1415 / (Scalar)length);
	Scalar one;
	int i;
	Vector sin_squared = lb_allocate_vector(1024l * length);
	Vector cos_squared = lb_allocate_vector(1024l * length);

	printf("About to create sin_squared\n");
	#pragma omp parallel for private(i)
	for(i = 0; i < sin_squared.length; i++) {
		sin_squared.data[i] = (Scalar)pow(sin(h * i),2);
	}

	printf("About to create cos_squared\n");
	#pragma omp parallel for private(i)
	for(i = 0; i < cos_squared.length; i++) {
		cos_squared.data[i] = (Scalar)pow(cos(h * i),2);
	}

	printf("About to create dot product\n");
	lbdp(sin_squared,cos_squared,&one);
	printf("Sin^2 + Cos^2 = %f\n",one);
	return 0;
}
