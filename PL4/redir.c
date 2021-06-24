#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main (int argc, char *argv[]) {
	if (argc < 2) {
		perror("redir [-i fich_entrada] [-o fich_saida] comando arg1 arg2");
		_exit(-1);
	}

	char *args[argc];
	int j = 0;
	for (int i = 1; i < argc; i++)  {
		if (strcmp("-i", argv[i]) == 0) {
			i++;	
			int fd = open(argv[i], O_RDONLY);
			if (fd == -1) { perror("Maybe invalid input"); _exit(-1); }
			dup2(fd, 0); close(fd);
	 	}
		else if (strcmp("-o", argv[i]) == 0) {
			i++;
			int fd = open(argv[i], O_WRONLY | O_TRUNC | O_CREAT, 0644);
			if (fd == -1) {perror("Maybe invalid input"); _exit(-1); }
			dup2(fd, 1);close(fd);
		}
		else args[j++] = argv[i];
		
	}

	args[j] = NULL;

	if (!fork()) {
		execvp(args[0], args);
		perror("Execution failed...");
		_exit(-1);
	}
	else wait(NULL);

	return 0;
}
