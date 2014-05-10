#include <math.h>
#include <cuda.h>

__global__ void apply_f1(double h, int lower_bound, double* destination) {
	int thread_id = blockDim.x * blockIdx.x + threadIdx.x;
	destination[thread_id] = sin(h * (thread_id + lower_bound));
}

__global__ void apply_f2(double h, int lower_bound, double* destination) {
	int thread_id = blockDim.x * blockIdx.x + threadIdx.x;
	destination[thread_id] = cos(h * (thread_id + lower_bound));
}

extern "C" void populate_vectors(double* f1, double* f2, unsigned int local_length, double h, unsigned int lower_bound) {
	double* f1_d;
	double* f2_d;
	size_t bytes = sizeof(double) * local_length;
	size_t threads = 1024;
	size_t blocks = local_length / threads;
	cudaMalloc(&f1_d, bytes);
	cudaMalloc(&f2_d, bytes);
	apply_f1<<<blocks,threads>>>(h,lower_bound,f1_d);
	apply_f2<<<blocks,threads>>>(h,lower_bound,f2_d);
	cudaDeviceSynchronize();
	cudaMemcpy(f1, f1_d, bytes, cudaMemcpyDeviceToHost);
	cudaMemcpy(f2, f2_d, bytes, cudaMemcpyDeviceToHost);
}
