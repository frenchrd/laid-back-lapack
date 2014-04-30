#include <stdlib.h>
#include <stdio.h>
#include "math.h"
#include "lb_vector.h"

int main(int argc, char** argv) {
	unsigned int length = atoi(argv[1]);

	Vector sin_squared = lb_allocate_vector(1024l * length);
	printf("About to create sin_squared\n");
	lbv_iterate(sin_squared, i, sin_squared.data[i] = (Scalar)pow(sin(h * i),2));

	Vector cos_squared = lb_allocate_vector(1024l * length);
	printf("About to create cos_squared\n");
	lbv_iterate(cos_squared, i, cos_squared.data[i] = (Scalar)pow(cos(h * i),2));

	Scalar one;
	printf("About to create dot product\n");
	lbdp(sin_squared,cos_squared,&one);
	printf("Sin^2 + Cos^2 = %f\n",one);
	return 0;
}
