#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_TOKENS 64

/* Function prototypes */
void shell_loop(void);
char *read_line(void);
char **split_line(char *line);
int execute_command(char **args);
int is_builtin(char *command);

#endif /* SHELL_H */

