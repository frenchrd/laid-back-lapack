#ifndef LB_VECTOR_INCLUDED
	#include "lb_scalar.h"
	// Assume Vector to be n rows by 1 column
	typedef struct {
		Scalar* data;
		unsigned int length;
	} Vector;

	Vector lb_create_vector(Scalar* data, unsigned int length);
	Vector lb_allocate_vector(unsigned int length);
	void lbdp(Vector a, Vector b, Scalar* result);
	void lbstv(Scalar s, Vector v, Vector result);
	#define lbv_iterate(vec, iter, expr) do{\
		unsigned int iter;\
		for(iter=0; iter < vec.length; iter++) {\
			expr;\
		}\
	} while(0);
	#define LB_VECTOR_INCLUDED
#endif
