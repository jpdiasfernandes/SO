#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	if(!fork()) {
		execlp("ls", "ls", "-la", NULL);
		perror("error executing ls");
		exit(-1);
	}
	else wait(NULL);

	return 0;
}
