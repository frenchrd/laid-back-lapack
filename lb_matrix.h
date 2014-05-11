#ifndef LB_MATRIX_INCLUDED
	typedef struct {
		double* data;
		unsigned int num_rows;
		unsigned int num_cols;
	} Matrix;
	Matrix lb_create_matrix(double* data, unsigned int num_rows, unsigned int num_cols);
	Matrix lb_allocate_matrix(unsigned int num_rows, unsigned int num_cols);
	
	#define lb_mat_element_ptr(A,i,j) (A.data + j * A.num_cols + i)
	#define lb_mat_element(A,i,j) A.data[j * A.num_cols + i]
	#define lb_mat_row_element(A,i,j) A.data[i * A.num_cols + j]
	#define lb_mat_col_element(A,i,j) A.data[j * A.num_cols + i]
	#define lb_vec_element_ptr(v,j) v.data + j;
	void lbmm(Matrix A, Matrix B, Matrix result);
	void lbma(Matrix A, Matrix B, Matrix result);
	#define LB_MATRIX_INCLUDED
#endif
