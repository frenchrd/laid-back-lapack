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
	#define lb_get_row(A,j) lb_create_vector(A.data + j * A.num_cols)
	#define lb_vec_element_ptr(v,j) v.data + j;
	// Assume Matrix A is LB_ROW_ORIENTED
	void lbmv_row(Matrix A, Vector b, Vector result);
	#define lb_get_col(A,i) lb_create_vector(A.data + i * A.num_rows);
	// Assume Matrix A is LB_COL_ORIENTED
	void lbmv_col(Matrix A, Vector b, Vector result);
	#define LB_MATRIX_INCLUDED
#endif
