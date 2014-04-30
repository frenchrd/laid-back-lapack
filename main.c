#include <stdlib.h>
#include <stdio.h>
#include "math.h"
#include "lb_vector.h"

int main(int argc, char** agrv) {
	unsigned int length = atoi(argv[1]);
	Vector sine_squared = lb_allocate_vector(1024 * 1024 * length);
	lbv_iterate(sine_squared, i, sine_squared.data[i] = pow(sine(2 * 3.1415 / length * i),2));

	Vector cosine_squared = lb_allocate_vector(1024 * 1024 * length);
	lbv_iterate(cosine_squared, i, cosine_squared.data[i] = pow(cosine(2 * 3.1415 / length * i),2));

	Scalar one;
	lbdp(sine_squared,cosine_squared,&one);
	printf("Sin^2 + Cos^2 = %f\n",one);
	return 0;
}
