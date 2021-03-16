#include <stdio.h>
#include <string.h> /* strcmp */
#include <stdlib.h> /* rand and atoi */
#include <unistd.h> /* essential defs and decls */
#include <sys/wait.h> /* wait and macros */
#include <time.h>

#define MAX_COL 4096
#define MAX_LINE 128
#define MAX_RANDOM 530000

int main (int argc, char *argv[]) {
	// To run through the matrix
	int i, j;
	// Stores the number to find
	int arg;
	// Stores status from child process
	int status;
	// Initializes random seed;
	srandom(time(NULL));

	int **mat = malloc(MAX_LINE * sizeof(char *));

	if (argc > 2) { perror("args: matriz number"); exit(1);}

	arg = atoi(argv[1]);

	for (i = 0; i < MAX_LINE; i++) {
		mat[i] = malloc(sizeof(int) * MAX_COL);
		for (j = 0; j < MAX_COL; j++) {
			int rnd = random();	
			// Gets a random number between 0 and MAX_RANDOM
			mat[i][j] = rnd % (MAX_RANDOM + 1);
		}
	}	

	// Just to guarantee that the code is working
	for(i = 0; i < MAX_LINE; i++) 
		mat[i][i] = i;
	
	dprintf(1, "Linhas: ");
	for (i = 0; i < MAX_LINE; i++) {
		if(fork()) {
			for(j = 0; j < MAX_COL; j++)
				if(mat[i][j] == arg) dprintf(1, "%d \n", i);
			close(1);
			_exit(1);
		}
	}

	printf("Done \n");
}
