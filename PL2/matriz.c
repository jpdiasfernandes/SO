#include <stdio.h>
#include <stdlib.h>   /* rand and atoi */
#include <string.h>   /* strcmp */
#include <sys/wait.h> /* wait and macros */
#include <time.h>     /* to seed random function */
#include <unistd.h>   /* essential defs and decls */

#define MAX_COL 4096
#define MAX_LINE 128
#define MAX_RAND 530000

int main(int argc, char *argv[]) {
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

	if (argc > 2) {
		perror("args: matriz number");
		exit(1);
	}

	int **mat = malloc(MAX_LINE * sizeof(char *));

	// Seeds random function with current time
	srandom(time(NULL));

	arg = atoi(argv[1]);

	for (i = 0; i < MAX_LINE; i++) {
		mat[i] = malloc(sizeof(int) * MAX_COL);
		for (j = 0; j < MAX_COL; j++) {
			int rnd = random();
			// Gets a random number between 0 and MAX_RAND
			mat[i][j] = rnd % (MAX_RAND + 1);
		}
	}

	for (i = 0; i < MAX_LINE; i++) mat[i][i] = i;

	// Creates MAX_LINE childs from the first parent
	for (i = 0; i < MAX_LINE && pid != 0; i++) {
		if ((pid = fork()) == -1) {
			perror("Unable to fork.");
			exit(1);
		}
	}
	// Child executing
	if (pid == 0) {
		for (j = 0; j < MAX_COL; j++)
			if (mat[i][j] == arg) exit(i);
		_exit(0);
	} else {
		for (i = 0; i < MAX_LINE; i++) {
			wait(&status);
			if (r == 0) r = WEXITSTATUS(status);
		}

		if (r) printf("Found the number in line %d", r);
	}

	return 0;
}

