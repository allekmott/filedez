#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define VERSION_NO "0.0.2"

void usage() {
	printf("Usage: filedez <file_to_dez>\n");
	exit(0);
}

// Crap out an error message and exit
void crap(char *msg) {
	fprintf(stderr, "An error occurred: %s\nError stuff: %s\n",
		msg, strerror(errno));
	exit(1);
}

// Encrypt a buffer of provided length
void encrypt_buffer(char *buffer, int len) {

}

// Encrypt source file, output to destination
void encrypt_file(FILE *src, FILE *dest) {
	printf("Encrypting file...\n");
	int buflen;
	char buf[buflen];
	while (fgets(buf, buflen, src) != NULL) {
		printf("Encrypting buffer '%s'\n", buf);
		encrypt_buffer(buf, buflen);
		fputs(buf, dest);
	}
}

void run(char *filename) {
	printf("File: %s\n", filename);

	FILE *file;
	if ((file = fopen(filename, "r")) == 0)
		crap("File shiz don't be existin'");

	printf("Opened stream to %s\n", filename);

	char new_filename[100];
	strcpy(new_filename, filename);
	strcat(new_filename, ".dez");
	
	printf("New filename: %s\n", new_filename);

	FILE *new_file;

	char nf_err_str[150];
	sprintf(nf_err_str, "Couldn't create %s\n", new_filename);

	if ((new_file = fopen(new_filename, "w+")) == 0)
		crap(nf_err_str);

	printf("File %s opened successfully.\n", new_filename);

	printf("\nBeginning encryption phase...\n");
	encrypt_file(file, new_file);

	fclose(file);
	fclose(new_file);
}

int main(int argc, char *argv[]) {
	printf("FileDez v%s\n", VERSION_NO);
	if (argc > 1)
		run(argv[1]);
	else
		usage();
	
}
