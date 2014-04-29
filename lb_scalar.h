#ifndef LB_SCALAR_INCLUDED
	#ifdef LB_SCALAR_DOUBLE
		typedef double Scalar;
	#else
		typedef float Scalar;
	#endif
	#define LB_SCALAR_INCLUDED
#endif
