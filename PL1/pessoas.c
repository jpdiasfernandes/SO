#include <unistd.h> /* open */
#include <stdio.h>
#include <stdlib.h> 
#include <fcntl.h> /* Values of oflag in function open */
#include <string.h> /* strncmp and strcpy and memcpy*/
#include <ctype.h> /* isdigit */
#include <sys/stat.h> /* fstat to get the file size */
#include <sys/types.h> /* To get stat struct */



#define MAX_NAME 60
#define MAX_BUFF 4096

typedef struct pessoa {
	char name[MAX_NAME];
	int age; 
} Pessoa;

int main (int argc, char *argv[]) {
	int f; // descritor do ficheiro de structs
	char buffer[MAX_BUFF];
	int insert, update; // local variable to determine the state of the second argument
	int reg = -1; //local variable to the registry entry of a unique person.
	int verbose = 1;

	if (argc > 5) { perror("args: pessoas -i | -u | name age"); exit(1); }

	if ( (insert = strcmp(argv[1], "-i")) && (update = strcmp(argv[1], "-u")) ) 
		{ perror("Wrong arguments"); exit(1);}

	if (argc == 5 && strcmp("--no-verbose", argv[4]) == 0) verbose = 0;

	if (!insert) {
		f = open("db", O_APPEND | O_CREAT | O_WRONLY, 0644);
		if (f == -1) 
			{ perror("Unable to open or create db file."); exit(1);}
		Pessoa insert;
		strncpy(insert.name, argv[2], MAX_NAME);
		insert.age = atoi(argv[3]);

		if ( write(f, &(insert), sizeof(Pessoa)) == -1)
			{perror("Unable to write on db file"); close(f); exit(1);}

		if(verbose) {
			//Getting the file size. Seems more elegant than doing fseek...
			struct stat buff;
			fstat(f, &buff); // gets the status of the file.

			reg = buff.st_size / sizeof(Pessoa);
			dprintf(1, "Inserted reg %d", reg);
		}
		
	}
	else if (!update) {
		f = open("db", O_RDWR);
		if (f == -1) {perror("Couldn't open file correctly."); exit(1);}

		Pessoa update;
		int age = atoi(argv[3]);
		if (isdigit(*argv[2]))  {
			int reg = atoi(argv[2]);
			lseek(f, reg*sizeof(Pessoa) - sizeof(Pessoa), SEEK_SET);
			read(f, &update, sizeof(Pessoa));
			// To revert read 
			lseek(f, -sizeof(Pessoa), SEEK_CUR);
			update.age = age;
			write(f, &update, sizeof(Pessoa));
		}
		else {
			int found = 0;
			while (!found && read(f, &(update), sizeof(Pessoa)) > 0) {
				if(strcmp(update.name, argv[2]) == 0) {
					update.age = age;
					lseek(f, -sizeof(Pessoa), SEEK_CUR);
					write(f, &(update), sizeof(Pessoa));
					found = 1;
				}	
			}
			if(!found){ perror("Unable to find the given name."); close(f); exit(1);}
		}

		if (verbose) {
			reg = lseek(f, 0, SEEK_CUR) / sizeof(Pessoa);
			dprintf(1, "Updated reg %d", reg);
		}

		
		close(f);
	}


	
	return 0;
}


	
