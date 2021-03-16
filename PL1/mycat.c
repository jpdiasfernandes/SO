/* 
 * Escreve o input no stdout
*/

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 4096

int main(int argc, char *argv[]) {
	int n;
	int f1 = 0, f2 = 1; // descritores de ficheiros; descritor do stdout = 1;
	char buffer[MAX];
	if (argc > 3) {
		perror("args: mycat source");
		exit(1);
	}
	
	while ( (n = read(f1, buffer, MAX)) > 0) 
		write(f2, buffer, n);

	close(f1);close(f2); // Fechar os descritores

	return 0;
}
