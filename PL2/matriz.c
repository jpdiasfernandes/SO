#include <stdio.h>
#include <string.h> /* strcmp */
#include <stdlib.h> /* rand and atoi */
#include <unistd.h> /* essential defs and decls */
#include <sys/wait.h> /* wait and macros */

#define MAX_COL 4096
#define MAX_LINE 128


int main (int argc, char *argv[]) {
	// To run through the matrix
	int i, j;
	// To get store the pid
	pid_t pid = getpid();
	// Stores the number to find
	int arg;
	// Stores the result of finding the arg number
	// if 0 then number not found else found
	int r = 0;
	// Stores status from child process
	int status;

	int **mat = malloc(MAX_LINE * sizeof(char *));

	if (argc > 2) { perror("args: matriz number"); exit(1);}

	arg = atoi(argv[1]);

	// O  meu raciocínio é que como o fork duplica todos os registos
	// também vai duplicar o pc. Deste modo só depois do fork é que 
	// o código vai ser executado. O que faz sentido, não vemos a 
	// main a ser executada mais que uma vez nos exemplos.
	
	for (i = 0; i < MAX_LINE; i++) {
		mat[i] = malloc(sizeof(int) * MAX_COL);
		for (j = 0; j < MAX_COL; j++) {
			// Although rand is not the most reliant peseudo-random
			// algorithm for the sake of an exercise like this
			// no need to use POSIX compliant functions.
			int rnd = random();	
			// Gets a random number between 0 and 250001
			mat[i][j] = rnd % 530001;
		}
	}	
	for(i = 0; i < MAX_LINE; i++) 
		mat[i][i] = i;
	
	for (i = 0; i < MAX_LINE && pid != 0; i++) {
		if ( (pid = fork()) == -1 ) { perror("Unable to fork."); exit(1);}
	}
	// Child executing
	if (pid == 0) {
		for (j = 0; j < MAX_COL; j++) 
			if (mat[i][j] == arg) exit(i);
		exit(0);
	}
	else {
		for (i = 0; i < MAX_LINE; i++) {
			wait(&status);
			if (r == 0) r = WEXITSTATUS(status);
		}

		if (r) printf("Found the number in line %d", r);

	}

	return 0;
}


