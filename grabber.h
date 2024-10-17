#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h> 
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

typedef uint8_t BYTE;

char* stor(char* in_buff, char* type, char* fn);

int fd_open(void);

void move(char* in, char *out);
void copy(char* in, char *out);


char *refile(char *folder, char *f_n);

char *combf(char *a, char *b);

int cntf(char *fold);
