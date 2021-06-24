#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#define MAX 4096

int main () {
	int d;

	if ( (d = open("/etc/passwd", O_RDONLY)) == -1 ) {
		perror("Erro while opening /etc/passwd");
		_exit(-1);
	}
	dup2(d, 0); close(d);

	if ( (d = open("lines", O_WRONLY | O_TRUNC | O_CREAT, 0644)) == -1 ) {
		perror("Error while creating or truncating lines file");
		_exit(-1);
	}
	dup2(d, 1); close(d);

	if (!fork()) {
		execlp("wc", "wc", NULL);
		perror("Error in wc");
		_exit(-1);
	}
	else wait(NULL);

	return 0;
}


