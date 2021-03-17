#include <stdio.h>
#include <string.h> /* strcmp */
#include <stdlib.h> /* rand and atoi */
#include <unistd.h> /* essential defs and decls */
#include <sys/wait.h> /* wait and macros */
#include <time.h>

#define MAX_COL 1048576
#define MAX_LINE 200
#define MAX_RANDOM 530000

int procura(int **mat, int linha, int arg) {
	int r = 0, j;
	for (j = 0; j < MAX_COL && !r; j++) 
		if(mat[linha][j] == arg) r++;
	return r;
}

int main (int argc, char *argv[]) {
	// To run through the matrix
	int i, j;
	// Stores the number to find
	int arg;
	// Stores status from child process
	int status;
	// To store the result of child process
	int r;
	// Stores child process ID
	pid_t pid;

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
	
	dprintf(1,"Linhas: ");
	for (i = MAX_LINE - 1; i >= 0; i--) {
		r = procura(mat, i, arg);

		// In the last cycle we don't want a new child
		if (i == 0) _exit(r);

		if( (pid = fork()) ) {
			waitpid(pid, &status, 0);
			if (WEXITSTATUS(status) == 1) dprintf(1, "| %d |", i - 1);
			_exit(r);
		}
	}

	//The code doesn't get here I think
	dprintf(1, "...");
	return 0;
}

