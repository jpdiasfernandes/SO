#include <sys/types.h>
#include <sys/stat.h>
#include "../PL1/readLn.h"
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define MAX_LINE 4096
int main(int argc, char *argv[]) {
	char buffer[MAX_LINE];

	if (argc == 2) {
		// strlen + the terminating null byte
		int count = strlen(argv[1]) + 1;
		int server = open("/tmp/server", O_WRONLY);

		write(server, argv[1], count);

		close(server);

		return 0;

	}
	return -1;
}
