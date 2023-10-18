#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdarg.h>

#define BUFFER 1024

extern char **environ;

/*
 * @ found: a byte to show wheather file is found or not
 * @ path: path if found otherwise NULL
*/
typedef struct 
{
	char found;
	char * path;
} file_status;

/*tokenize a string*/
char ** tokenize(char * buffer, short EOL);

char * _getenv(const char *name);

file_status *file_exists(char *name);

char *concatenate(int count, ...);
#endif
