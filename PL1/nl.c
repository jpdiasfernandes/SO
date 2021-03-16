#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "readLn.h"

#define MAX 4096

int main(int argc, char *argv[]) {
	int n, i = 1;
	int f1; // descritores de ficheiros
	char buffer[MAX];
	char num[3] = { '1', ':', ' '};
	if (argc > 2) {
		perror("args: mycp source dest");
		exit(1);
	}
	
	if ((f1 = open(argv[1], O_RDONLY)) == -1) {
		perror("open source"); 
		exit(1);
	}

	while ( (n = readln(f1, buffer, MAX)) > 0 ) {
		dprintf(1, "%d ", i);
		write(1, buffer, n);
		num[0] = '0' + i++;
	}

	close(1);

	return 0;

}
