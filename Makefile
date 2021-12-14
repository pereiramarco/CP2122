COMPILER = gcc
FLAGS = -O2 -c -g -Wall
FLAGS_OPENMP = -fopenmp -lm
FLAGS_LINK = -O2 -g -Wall -lm

aux: 
	$(COMPILER) $(FLAGS) src/aux.c -o aux.o

parallel: 
	$(COMPILER) $(FLAGS) $(FLAGS_OPENMP) src/parallel.c -o parallel.o

sequential: 
	$(COMPILER) $(FLAGS) src/sequential.c -o sequential.o

sort:
	$(COMPILER) $(FLAGS) main.c -o sort.o

main: sequential sort parallel aux
	$(COMPILER) $(FLAGS_LINK) $(FLAGS_OPENMP) sort.o sequential.o parallel.o aux.o -o sort

run: main
	./sort $(size) $(max_number) $(running_type)


clean: 
	rm -rf *.o sort