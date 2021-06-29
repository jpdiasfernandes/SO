#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#define MAX_SIZE 4096

struct files {
	int pipe;
	int log;
};

volatile struct files fd;

static void terminate(int sig) {
	close(fd.log);
	close(fd.pipe);
	printf("Received a signal\n");
	_exit(0);
}

int main(int argc, char *argv[]) {
	char buf[MAX_SIZE];
	ssize_t n;
	signal(SIGTERM, terminate);	

	int fifo = mkfifo("/tmp/server", 0644);
	int pipe = open("/tmp/server", O_RDONLY);
	fd.pipe = pipe;
	int log = open("log.txt", O_APPEND | O_CREAT | O_WRONLY, 0666);
	fd.log = log;

	while(1) {
		if ( (n = read(pipe, buf, MAX_SIZE)) > 0) {
			write(log, buf, n);
		}
	}

}
