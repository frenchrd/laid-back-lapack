#include <stdlib.h>
#include <stdio.h>
#include "lb_walltimer.h"
#include "lb_matrix.h"

int main(int argc, char** argv) {
	Matrix a = lb_allocate_matrix(2,3);
	Matrix b = lb_allocate_matrix(3,1);
	Matrix c = lb_allocate_matrix(2,1);
	int row,col,element_id;

	// Populate matrix A
	element_id = 0;
	for(row = 0; row < a.num_rows; row++) {
		for(col = 0; col < a.num_cols; col++) {
			element_id++;
			lb_mat_row_element(a,row,col) = element_id;
		}
	}
	printf("a[0,0] == %f\n", lb_mat_element(a,0,0));
	printf("a[0,1] == %f\n", lb_mat_element(a,0,1));
	printf("a[0,2] == %f\n", lb_mat_element(a,0,2));
	printf("a[1,0] == %f\n", lb_mat_element(a,1,0));
	printf("a[1,1] == %f\n", lb_mat_element(a,1,1));
	printf("a[1,2] == %f\n", lb_mat_element(a,1,2));

	// Populate matrix B
	element_id = 0;
	for(row = 0; row < b.num_rows; row++) {
		for(col = 0; col < b.num_cols; col++) {
			element_id++;
			lb_mat_col_element(b,col,row) = element_id;
		}
	}
	printf("b[0,0] == %f\n", lb_mat_element(b,0,0));
	printf("b[1,0] == %f\n", lb_mat_element(b,1,0));
	printf("b[2,0] == %f\n", lb_mat_element(b,2,0));
	

	// C = A * B
	lbmm(a,b,c);

	printf("c[0,0] == %f\n", lb_mat_element(c,0,0));
	printf("c[1,0] == %f\n", lb_mat_element(c,1,0));
	return 0;
}
