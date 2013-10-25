/* filedez.c
 * Created: 24 Oct 2013
 * Author: Allek Mott
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define VERSION_NO "0.0.0"

void usage();
void crap(char *msg);
void encrypt_buffer(char *buffer, int len);
void run(char *filename);
int main(int argc, char *argv[]);
