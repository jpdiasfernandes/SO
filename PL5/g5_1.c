#include <unistd.h>
#define MAX 4096

int main () {
	int p[2];
	pipe(p);
	int l;
	char buf[MAX];

	if(!fork()) {
		// To prevent deadlocks
		close(p[1]);
		l = read(p[0], buf, MAX);
		write(1, buf, l);
	}
	else {
		// To prevent deadlocks
		close(p[0]);
		l = read(0, buf, MAX);
		sleep(5);
		write(p[1], buf, l);
	}
	return 0;
}
