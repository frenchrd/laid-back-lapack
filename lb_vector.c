#include <stdlib.h>
#include "lb_vector.h"

Vector lb_create_vector(double* data, unsigned int length) {
	Vector v;
	v.data = data;
	v.length = length;
	return v;
}

Vector lb_allocate_vector(unsigned int length) {
	double* ptr = (double*)malloc(sizeof(double) * length);
	return lb_create_vector(ptr, length);
}

// Result = Vector dot Vector
void lbdp(Vector a, Vector b, double* result) {
	*result = 0.0;
	int i;
	double inner_result;
	#pragma omp parallel for default(none) shared(a,b) private(i) reduction(+:inner_result)
	for(i = 0; i < a.length; i++) inner_result += a.data[i] * b.data[i];
	*result = inner_result;
}

// Result = Vector + Vector
void lbvpv(Vector a, Vector b, Vector result) {
	int i;
	#pragma omp parallel for private(i)
	for(i=0; i < a.length; i++) result.data[i] = a.data[i] + b.data[i];
}

// Result = double * Vector
void lbstv(double s, Vector v, Vector result) {
	int i;
	for(i = 0; i < v.length; i++) result.data[i] = s * v.data[i];
}
