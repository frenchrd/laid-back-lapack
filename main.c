#include <stdlib.h>
#include <stdio.h>


// Result = Scalar * Vector
void lbstv(Scalar s, Vector v, Vector result) {
	int i;
	for(i = 0; i < v.length; i++) result.data[i] = s * v.data[i];
}
