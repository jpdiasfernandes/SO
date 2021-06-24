#include <unistd.h>

int main() {
	int p[2];
	pipe(p);
	if (!fork()) {
		close(p[1]);
		dup2(p[0], 0);
		close(p[0]);
		execlp("wc", "wc", "-l" ,NULL);
	}
	else {
		close(p[0]);
		dup2(p[1], 1);
		close(p[1]);
		execlp("ls", "ls", "/etc", NULL);
	}
}
