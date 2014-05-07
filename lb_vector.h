#ifndef LB_VECTOR_INCLUDED
	// Assume Vector to be n rows by 1 column
	typedef struct {
		double* data;
		unsigned int length;
	} Vector;

	Vector lb_create_vector(double* data, unsigned int length);
	Vector lb_allocate_vector(unsigned int length);
	void lbdp(Vector a, Vector b, double* result);
	void lbstv(double s, Vector v, Vector result);
	#define LB_VECTOR_INCLUDED
#endif
