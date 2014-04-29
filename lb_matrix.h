#ifndef LB_MATRIX_INCLUDED
	#include "lb_scalar.h"
	// Orientation determines whether rows or columns are contiguous in memory
	typedef enum {LB_ROW_ORIENTED, LB_COL_ORIENTED} MatrixOrientation;

	typedef struct {
		Scalar* data;
		unsigned int num_rows;
		unsigned int num_cols;
		MatrixOrientation orientation;
	} Matrix;
	
	#define lb_mat_element_ptr(A,i,j) (A.data + j * A.num_cols + i)
	void lbmm(Matrix A, Matrix B, Matrix result);
	#define LB_MATRIX_INCLUDED
#endif
