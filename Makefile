trig.exe: main.c lb_vector.o
	cc main.c -o trig.exe lb_vector.o
	
lb_vector.o: lb_scalar.h lb_vector.h lb_vector.c
	cc -fopenmp lb_vector.c -c lb_vector.o

clean:
	rm -f *.o
	rm -f *.exe
