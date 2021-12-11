COMPILER = gcc
FLAGS = -O2 -g -c -Wall
FLAGS_LINK = -O2 -g -Wall -lm

sequential: 
	$(COMPILER) $(FLAGS) src/sequential.c -o sequential.o

sort:
	$(COMPILER) $(FLAGS) main.c -o sort.o

main: sequential sort
	$(COMPILER) $(FLAGS_LINK) sort.o sequential.o -o sort

run: main
	./sort $(size) $(max_number) $(running_type)


clean: 
	rm -rf *.o sort