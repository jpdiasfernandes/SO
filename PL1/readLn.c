/*
  Testa a função aqui definida readLn
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#define MAX 4096

size_t readln(int fd, char *line, size_t size) {
	static char buff[MAX];
	static int count = 0; // necessária para aceder a nova linha numa nova invocação
	static int upper = 0; // variável necessária para fazer round-robin com a variável count
	size_t i = 0; 

	if (count == 0 && (upper = read(fd, buff, MAX)) <= 0 ) return -1;
	
	while (i < size && (count + i) < upper && buff[count + i] != '\n') {
		line[i] = buff[count + i];
		i++;
	}

	if (i < size && (count + i) < MAX){ line[i] = buff[count + i]; i++;}
	
	
	count = (count + i)%upper;

	return i;
}

