#include "lb_matrix.h"
// Assume A.num_cols == B.num_rows
// Assume A.num_rows == B.num_cols
void lbmm(Matrix A, Matrix B, Matrix result) {
	int col,row,offset,vec_length;
	double temp;
	vec_length = A.num_cols;
	for(int col = 0; col < A.num_cols; col++) {
		for(row = 0; row < A.num_rows; row++) {
			// Dot Product Row_i(A) with Col_j(B)
			temp = 0.0;
			for(offset = 0; offset < vec_length; offset++) {
				temp += lb_mat_row_element(A,row,offset) * lb_mat_col_element(B,col,offset);
			}
			lb_mat_element(result,row,col) = temp;
		}
	}
}


// Assume A.num_cols == B.num_cols
// Assume A.num_rows == B.num_rows
void lbma(Matrix A, Matrix B, Matrix result) {
	int col,row;
	for(int col = 0; col < A.num_cols; col++) {
		for(row = 0; row < A.num_rows; row++) {
			lb_mat_element(result,row,col) = lb_mat_element(A,row,col) + lb_mat_element(B,row,col);
		}
	}
}

Matrix lb_create_matrix(double* data, unsigned int num_rows, unsigned int num_cols) {
	Matrix m;
	m.data = data;
	m.num_rows = num_rows;
	m.num_cols = num_cols;
	return m;
}

Matrix lb_allocate_matrix(unsigned int num_rows, unsigned int num_cols) {
	double* ptr = (double*)malloc(sizeof(double) * num_rows * num_cols);
	return lb_create_matrix(ptr,num_rows,num_cols);
}
