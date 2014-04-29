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

