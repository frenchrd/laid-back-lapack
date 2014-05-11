#include "lb_matrix.h"
#include <stdlib.h>
// Assume A.num_cols == B.num_rows
// 	  C.num_rows == A.num_rows
// 	  C.num_cols == B.num_cols
void lbmm(Matrix A, Matrix B, Matrix result) {
	int col,row,offset,vec_length;
	double vec_sum;
	vec_length = A.num_cols;
	for(col = 0; col < B.num_cols; col++) {
		for(row = 0; row < A.num_rows; row++) {
			// Dot Product Row(A) with Col(B)
			vec_sum = 0.0;
			for(offset = 0; offset < vec_length; offset++) {
				double a = lb_mat_row_element(A,row,offset);
				double b = lb_mat_col_element(B,col,offset);
				double product = a * b;
				vec_sum += product;
			}
			lb_mat_element(result,row,col) = vec_sum;
		}
	}
}


// Assume A.num_cols == B.num_cols
// Assume A.num_rows == B.num_rows
void lbma(Matrix A, Matrix B, Matrix result) {
	int col,row;
	for(col = 0; col < A.num_cols; col++) {
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
