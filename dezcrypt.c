/*
 * dezcrypt.c
 * Created: 26 October 2013
 * Author: Allek Mott
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#include "dezcrypt.h"

// Crap out an error message and exit
void crap(char *msg) {
	fprintf(stderr, "An error occurred: %s\nError string: %s\n",
		msg, strerror(errno));
	exit(1);
}
int dc_get_char_shift(int pos, int buflen) {
	int shift;
	if (pos % 2 == 1)
		shift = (0 + ((pos + 1)/2));
	else
		shift = (buflen - ((pos/2)));
	return shift;
}

void dc_crypt_char(char *c, int pos, int buflen, int decrypt) {
	if (*c == '\0')
		return;
	int shift = dc_get_char_shift(pos, buflen);

	// if decrypting and pos is odd, subtract 1 from thingy
	char offset = (decrypt && (pos % 2 == 1)) ? 1 : 0;

	char c0 = *c;
	printf("Shift = %i; c0 = '%c' = %i; ", shift, c0, (int) *c);
	if (decrypt)
		*c = ((*c - shift) << 1) + offset;
	else
		*c = (*c >> 1) + shift; // bit shift right, add char shift

	int diff = (c0 - *c);
	if (diff == -1) {
		*c -= 1;
		diff = 0;
	}

	printf("After: '%c' = %i; Diff: %i\n", *c, (int) *c, diff);
}

void dc_crypt_buffer(char *buffer, int len, int decrypt) {
	if (decrypt)
		printf("\nDecrpyting buffer '%s'\n", buffer);
	else
		printf("\nEncrypting buffer '%s'\n", buffer);

	int c_no;
	for (c_no = 0; c_no < len; c_no++)
		dc_crypt_char(&buffer[c_no], c_no, len, decrypt);
}

#define BUFFER_LENGTH 57

void dc_crypt_stream(int src_fd, int dest_fd, int decrypt) {
	if (decrypt)
		printf("Decrypting file...\n");
	else
		printf("Encrypting file...\n");
	char buf[BUFFER_LENGTH];
	char *current = buf;
	int cur_no = 0;
	while (read(src_fd, current, 1) != 0) {
		if (*current == '\0')
			continue;
		if ((cur_no + 1) == BUFFER_LENGTH) {
			dc_crypt_buffer(buf, BUFFER_LENGTH, decrypt);
			write(dest_fd, buf, BUFFER_LENGTH);
			memset(buf, 0, BUFFER_LENGTH); // zero out buffer
			current = buf;
			cur_no = 0;
		}
		current++;
		cur_no++;
	}
	if (cur_no != 0) {
		// no increment of cur_no, as last buffer has file terminator
		printf("Chars remaining: %i\n", cur_no);
		dc_crypt_buffer(buf, cur_no, decrypt);
		write(dest_fd, buf, cur_no);
	}
}

void dc_crypt(int src_fd, int dest_fd, int decrypt) {
	if (decrypt)
		printf("\nBeginning decryption...\n");
	else
		printf("\nBeginning encryption...\n");

	dc_crypt_stream(src_fd, dest_fd, decrypt);
	printf("\n");
}