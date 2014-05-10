trig.exe: main.c lb_vector.o populate_vectors.o
	cc -g -fopenmp main.c -o trig.exe lb_vector.o populate_vectors.o
	cp trig.exe $(MEMBERWORK)/stf007
	
populate_vectors.o: populate_vectors.cu
	nvcc -arch=sm_35 -c populate_vectors.cu

lb_vector.o: lb_vector.h lb_vector.c
	cc -g -fopenmp lb_vector.c -c 

clean:
	rm -f *.o
	rm -f *.exe
