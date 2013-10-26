#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define VERSION_NO "0.0.4"
#define BUFFER_LENGTH 57

int decrypt = 0;

void usage() {
	printf("Usage: filedez <file_to_dez>\n");
	exit(0);
}

// Crap out an error message and exit
void crap(char *msg) {
	fprintf(stderr, "An error occurred: %s\nError string: %s\n",
		msg, strerror(errno));
	exit(1);
}

// Calculate a bit shift for the provided char position
int get_char_shift(int pos, int buflen) {
	int shift;
	if (pos % 2 == 1)
		shift = (0 + ((pos - 1)/2));
	else
		shift = (buflen - ((pos/2)));
	return shift;
}

void encrypt_char(char *c, int pos, int buflen) {
	int shift = get_char_shift(pos, buflen);
	//printf("Shifting char '%c' %i up", *c, shift);
	*c = (*c >> 1) + shift; // bit shift right, add char shift
	//printf(" = %c\n", *c);
}

// Encrypt a buffer of provided length
void encrypt_buffer(char *buffer, int len) {
	printf("\nEncrypting buffer '%s'\n", buffer);
	int c_no;
	for (c_no = 0; c_no < len; c_no++) {
		if (buffer[c_no] == '\0')
			return;
		encrypt_char(&buffer[c_no], c_no, len);
	}
}

// Encrypt source file, output to destination
void encrypt_stream(int src_fd, int dest_fd) {
	printf("Encrypting file...\n");
	char buf[BUFFER_LENGTH];
	while (read(src_fd, buf, BUFFER_LENGTH) != 0) {
		encrypt_buffer(buf, BUFFER_LENGTH);
		write(dest_fd, buf, BUFFER_LENGTH);
	}
}

void encrypt(int src_fd, int dest_fd) {
	printf("\nBeginning encryption phase...\n");
	encrypt_stream(src_fd, dest_fd);
	printf("\n");
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
	char new_filename[100];
	strcpy(new_filename, filename);
	strcat(new_filename, ".dez");
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
				if (argv[2] != "")
					open_src_file(argv[2], src_fd);
				break;
			default: usage();
		}
	} else
		file_stuff(argv[1], src_fd, dest_fd);
}

int main(int argc, char *argv[]) {
	if (argc > 1) {
		int src_fd = 0, dest_fd = 1;
		manage_args(argc, argv, &src_fd, &dest_fd);
		printf("FileDez v%s\n", VERSION_NO);
		encrypt(src_fd, dest_fd);
	} else
		usage();
	
	cleanup();
}
