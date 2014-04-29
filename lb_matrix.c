#include "lb_matrix.h"
// Assume Matrix A is LB_ROW_ORIENTED
// Assume Matrix B is LB_COL_ORIENTED
void lbmm(Matrix A, Matrix B, Matrix result) {
	int i,j;
	for(int j = 0; j < A.num_cols; j++) {
		Vector A_j = lb_get_row(A,j);
		for(i = 0; i < A.num_rows; i++) {
			Vector B_i = lb_get_col(B,i);
			Scalar* result_element = lb_mat_element_ptr(result,i,j);
			lbdp(A_j, B_i, result_element);
		}
	}
	result.orientation = LB_ROW_ORIENTED;
}

