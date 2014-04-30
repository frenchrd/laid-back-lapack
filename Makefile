trig.exe: main.c lb_vector.o
	cc main.c -o trig.exe lb_vector.o 
	cp trig.exe $(MEMBERWORK)/stf007
	
lb_vector.o: lb_scalar.h lb_vector.h lb_vector.c
	cc -fopenmp lb_vector.c -c 

clean:
	rm -f *.o
	rm -f *.exe
