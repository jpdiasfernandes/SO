/* 
 * Copia ficheiros 
*/

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 4096

int main(int argc, char *argv[]) {
	int n;
	int f1, f2; // descritores de ficheiros
	char buffer[MAX];
	if (argc > 3) {
		perror("args: mycp source dest");
		exit(1);
	}
	
	if ((f1 = open(argv[1], O_RDONLY)) == -1) {
		perror("open source"); 
		exit(1);
	}

	if ((f2 = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0644)) == -1) {
		perror("open dest");
		exit(1);
	}

	while ( (n = read(f1, buffer, MAX)) > 0) 
		write(f2, buffer, n);

	close(f1);close(f2); // Fechar os descritores

	return 0;
}
