#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include "../PL1/readLn.h"

#define MAX_ELEM 32
#define MAX 4096
char **parse_arg(char *execs, int *elems, const char *delim) {
	char *tmp = strdup(execs);
	char *token, *str;
	char *saveptr;
	char **r = calloc(MAX_ELEM,sizeof(char *));
	int i = 0, max = MAX_ELEM;
	for(str = tmp; ; str = NULL) {
		token = strtok_r(str, delim, &saveptr);
		if(token == NULL) break;
		if (i == max){
			max *=2;
			r = realloc(r, max);
			if (r == NULL) perror("Args array realloc failed.");
		}
		r[i++] = strdup(token);
	}
	*elems = i;
	free(tmp);
	return r;
}
int my_system(char *execs) {
	int elems = 0;
	char **args = parse_arg(execs, &elems, " ");
	int exit_stat;
	int i;
	if(!fork()) {
		execvp(*args, args);
		perror("Error");
		return -1;
	}

	wait(&exit_stat);
	while(i < elems) {
		free(args[i]);
		i++;
	}
	free(args);
	return exit_stat;
}

