#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
int main(int argc, char *argv[]) {
	int i;
	char *args[4][4] = { {"cat", "teste.txt", NULL, NULL} , {"grep", "-i", "hello", NULL} , {"uniq", NULL, NULL, NULL}, {"wc", "-l", NULL, NULL} };

	int fd[2];

	pipe(fd);
	for (int i = 0; i < 4; i++) {
		if (!fork()) {
			close(fd[0]);
			if (i != 3) 
				dup2(fd[1], 1);
			close(fd[1]);

			execvp(args[i][0], args[i]);
			perror("Error while executing");
			_exit(-1);
		}
		else {
			close(fd[1]);
			if (i != 3) {
				dup2(fd[0], 0);
				close(fd[0]);
				pipe(fd);
			}
			else close(fd[0]);
		}
	}
	for (int i = 0; i < 4; i++)
		wait(NULL);
	_exit(0);

}
