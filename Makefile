all: test_pq

test_pq: dynarray.o pq.o test_pq.c
	gcc -Wall --std=c99 -g test_pq.c dynarray.o pq.o -o test_pq

pq.o: pq.c pq.h dynarray.h
	gcc -Wall --std=c99 -g -c pq.c

dynarray.o: dynarray.c dynarray.h
	gcc -Wall --std=c99 -g -c dynarray.c

clean:
	rm -f *.o test_pq
