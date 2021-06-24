#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#define MAX 4096

int main () {
	int d;

	if ( (d = open("erros.txt", O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1) {
		perror("Error in erros.txt");
		_exit(-1);
	}
	dup2(d, 2);close(d);

	if ( (d = open("/etc/passwd", O_RDONLY))  == -1) {
		perror("Error opening /etc/passwd");
		_exit(-1);
	}
	dup2(d, 0); close(d);

	if ( (d = open("out.txt", O_WRONLY | O_CREAT | O_APPEND , 0644)) == -1) {
		perror("Error in out");
		_exit(-1);
	}
	dup2(d, 1);close(d);
	
	if (!fork()) {
		// O fork é só para mostrar que as associações de descritores de ficheiros se mantêm iguais ao do processo do pai
		int n;
		char buf[4096];
		if ( (n = read(0, buf, 10)) > 0)
			write(1, buf, n);

		while ( (n = read(0, buf, MAX)) > 0)
			write(2, buf, n);



	}
	else wait(NULL);
	
}
