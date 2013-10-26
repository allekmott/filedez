#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dezcrypt.h"

#define VERSION_NO "0.0.5"

int decrypt = 0;

void usage() {
	printf("Usage: filedez <file_to_dez>\n");
	exit(0);
}

// Source file, destination file
FILE *src_file, *dest_file; 

void open_src_file(char *filename, int *src_fd) {
	printf("File: %s\n", filename);
	if ((src_file = fopen(filename, "r")) == 0)
		crap("Input file shiz don't be existin'");
	printf("Opened stream to %s\n", filename);
	*src_fd = fileno(src_file);
}

void open_dest_file(char *filename, int *dest_fd) {
	char *ext = (decrypt) ? ".undez" : ".dez";
	char new_filename[100];
	strcpy(new_filename, filename);
	strcat(new_filename, ext);
	printf("New filename: %s\n", new_filename);

	char nf_err_str[150];
	sprintf(nf_err_str, "Couldn't create %s\n", new_filename);

	if ((dest_file = fopen(new_filename, "w+")) == 0)
		crap(nf_err_str);

	printf("File %s opened successfully.\n", new_filename);
	
	*dest_fd = fileno(dest_file);
}

void file_stuff(char *filename, int *src_fd, int *dest_fd) {
	open_src_file(filename, src_fd);
	open_dest_file(filename, dest_fd);
}

void close_files() {
	if (src_file != NULL)
		fclose(src_file);
	if (dest_file != NULL)
		fclose(dest_file);
}

void cleanup() {
	printf("Cleaning up.\n");
	close_files();
}

void manage_args(int argc, char *argv[], int *src_fd, int *dest_fd) {
	if (argv[1][0] == '-') {
		switch (argv[1][1]) {
			case 'c':
				printf("Output set to console.\n");
				*dest_fd = 1;
				if (strcmp(argv[2], ""))
					open_src_file(argv[2], src_fd);
				break;
			case 'd':
				printf("Decrypting.\n");
				decrypt = 1;
				file_stuff(argv[2], src_fd, dest_fd);
				break;
			default: usage();
		}
	} else
		file_stuff(argv[1], src_fd, dest_fd);
}

int main(int argc, char *argv[]) {
	printf("FileDez v%s\n", VERSION_NO);
	if (argc > 1) {
		int src_fd = 0, dest_fd = 1;
		manage_args(argc, argv, &src_fd, &dest_fd);
		dc_crypt(src_fd, dest_fd, decrypt);
	} else
		usage();
	
	cleanup();
}
