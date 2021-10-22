#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int start;
	int stop;
	int step;
	int number;
	int current_elem;
} range;


void argparse(int argcount, char** argvec, int* start, int* stop, int* step) {
	if (argcount < 2 || argcount > 4) {
		printf("\nHELP: ./range M {N {S}} (M, N, S - integers && S != 0)\n\n");
		printf("./range M -> output: [0, 1, ..., M-1] (if M > 0)\n\n");
		printf("./range M N -> output: [M, M+1, ..., N-1] (if N > M)\n\n");
		printf("./range M N S -> output: [M, M+S, ..., N-1] (if N > M && S > 0 || N < M && S < 0)\n\n");
		*start = 0; *stop = -1; *step = 0;
	}
	else {
		*start = argcount > 2 ? atoi(argvec[1]) : 0;
		*stop = argcount > 2 ? atoi(argvec[2]) : atoi(argvec[1]);
		*step = argcount > 3 ? atoi(argvec[3]) : 1;
	}
}


void range_init(range* I) {
	I->number = 1;
	I->current_elem = I->start;
}


_Bool range_run(range* I) {
	if (I->step > 0) return I->current_elem < I->stop;
	else return I->step != 0 && I->current_elem > I->stop;
}


void range_next(range* I) {
	I->current_elem += I->step;
	I->number++;
}


int range_get(range* I) {
	return I->current_elem;
}


int main(int argc, char *argv[]) {
        range I;
        argparse(argc, argv, &I.start, &I.stop, &I.step);
        for(range_init(&I); range_run(&I); range_next(&I)) 
		printf("%d\n", range_get(&I));
        return 0;
}
