#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
	execlp("ls", "ls", "-l", NULL);
	perror("ls didn't work"); 
	exit(-1); 
}
