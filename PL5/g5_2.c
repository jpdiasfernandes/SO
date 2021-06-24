#include <unistd.h>
#define MAX 4096
int main() {
	int p[2];
	pipe(p);
	int n;
	char buf[MAX];

	if(!fork()) {
		close(p[1]);
		while( (n = read(p[0], buf, MAX) )  > 0)
			write(1, buf, n);
		close(p[0]);
	}
	else {
		close(p[0]);
		while ( (n = read(0, buf, MAX)) > 0 )
			write(p[1], buf, n);
		close(p[1]);
	}

	return 0;
}
