#include "lb_vector.h"

Vector lb_create_vector(Scalar* data, unsigned int length) {
	Vector v;
	v.data = data;
	v.length = length;
	return v;
}

Vector lb_allocate_vector(unsigned int length) {
	void* ptr = malloc(sizeof(Scalar) * length);
	return lb_create_vector((Scalar*) ptr, length);
}

// Result = Vector dot Vector
void lbdp(Vector a, Vector b, Scalar* result) {
	&result = 0.0;
	int i;
	for(i = 0; i < a.length; i++) &result += a.data[i] * b.data[i];
}

// Result = Scalar * Vector
void lbstv(Scalar s, Vector v, Vector result) {
	int i;
	for(i = 0; i < v.length; i++) result.data[i] = s * v.data[i];
}
