#ifndef LB_VECTOR_INCLUDED
	#include "lb_scalar.h"
	// Assume Vector to be n rows by 1 column
	typedef struct {
		Scalar* data;
		unsigned int length;
	} Vector;

	Vector lb_create_vector(Scalar* data, unsigned int length);
	Vector lb_allocate_vector(unsigned int length);
	#define LB_VECTOR_INCLUDED
#endif
