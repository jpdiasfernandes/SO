#include <unistd.h>
#include <sys/wait.h>
#define MAX 4096

int main() {
	int p[2];
	pipe(p);
	char buf[MAX];
	int n;
	if (!fork()) {
		close(p[1]);
		dup2(p[0], 0);
		execlp("wc", "wc", NULL);
	}
	else {
		close(p[0]);
		while ( (n = read(0, buf, MAX)) > 0 )
			write(p[1], buf, n);
		close(p[1]);
		wait(NULL);
	}
}
