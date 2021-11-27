#include <stdio.h>
#include <stdlib.h>
#include "buf.h"

int main(int argc, char *argv[]) {

	long *a = 0;
	long i;
	int count = (argc > 1) ? atoi(argv[1]) : 10;
	for (i = 0; i < count; i += 1) buf_push(a, i);
	printf("Capacity: %d\n", (int)(buf_capacity(a)));
	int size = (int)buf_size(a);
	printf("Size: %d\n", size);
	printf("Elements:\n");
	for (i = 0; i < size; i += 1) 
		printf("%ld\n", buf_pop(a));
	buf_clear(a);
	printf("Size after clear: %d\n", (int)(buf_size(a)));
	buf_free(a);
	return 0;

}