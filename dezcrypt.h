/* dezcrypt.c
 * Created: 26 October 2013
 * Author: Allek Mott
 */

// 'Craps' out an error message and exits
void crap(char *msg);

/*
 * Calculate amount to shift char based on buffer length
 * and the provided char position
 */
int dc_get_char_shift(int pos, int buflen);

// Crypt a single character
void dc_crypt_char(char *c, int pos, int buflen, int decrypt);

// Crypt a buffer of provided length
void dc_crypt_buffer(char *buffer, int len, int decrypt);

// Crypt source stream, output to dest stream
void dc_crypt_stream(int src_fd, int dest_fd, int decrypt);

/*
 * Crypt input from the provided src_fd, output to the
 * provided dest_fd.
 */
void dc_crypt(int src_fd, int dest_fd, int decrypt);

