#include <stdio.h>
#include <stdlib.h>

#define VERSION_NO "0.0.1"

void usage() {
	printf("Usage: filedez <file_to_dez>");
	exit(0);
}

void crap(char *msg) {
	fprintf(stderr, "An error occurred: %s\n", msg);
}

char *encrypt_buffer(char *buffer, int len) {

}

void run(char *file_name) {
	printf("File: %s\n", file_name);
	FILE *file;
	if ((file = fopen(file_name, "r")) == NULL)
		crap("File shiz don't be existin'");

	

	fclose(file);
}

int main(int argc, char *argv[]) {
	printf("FileDez v%s\n", VERSION_NO);
	if (argc > 1) {
		run(argv[1]);
	else
		usage();
	
}
