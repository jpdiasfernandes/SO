#include "../PL1/readLn.h"
#include "system.h"
#include <unistd.h>
#define MAX 4096
int main () {
	char buf[MAX];
	int n;

	write(1, "MUCH WOW ~>", 11);
	while((n = readln(0, buf, MAX - 1) ) > 0) {
		if (buf[n - 1] == '\n') buf[n - 1] = '\0';
		my_system(buf);
		write(1, "MUCH WOW ~>", 11);
	}
	return 0;
}
