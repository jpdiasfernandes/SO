#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	int i;
	for (i = 1; i < argc; i++) {
		if (!fork()) {
			execlp(argv[i], argv[i], NULL);
			perror("Failed to execute the binary correctly.");
			_exit(-1);
		}
	}
	for(i = 1; i < argc; i++)
		wait(NULL);

	return 0;
}
