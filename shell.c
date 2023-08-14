#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX_INPUT_SIZE 1024

void display_prompt(void) 
{
printf("#cisfun$ ");
}
int main(void) 
{
char input[MAX_INPUT_SIZE];
while (1) 
{
display_prompt();
if (fgets(input, sizeof(input), stdin) == NULL) 
{
if (feof(stdin)) 
{
printf("\n");
break; 
}
perror("fgets");
exit(EXIT_FAILURE);
}
input[strcspn(input, "\n")] = '\0'; 
char *args[MAX_INPUT_SIZE];
int arg_count = 0;
char *token = strtok(input, " ");
while (token != NULL) 
{
args[arg_count++] = token;
token = strtok(NULL, " ");
}
args[arg_count] = NULL; 
pid_t child_pid = fork();
if (child_pid == -1) 
{
perror("fork");
exit(EXIT_FAILURE);
} 
else if (child_pid == 0) 
{
if (execvp(args[0], args) == -1) 
{
perror("execvp");
exit(EXIT_FAILURE);
}
} 
else 
{
int status;
if (waitpid(child_pid, &status, 0) == -1) 
{
perror("waitpid");
exit(EXIT_FAILURE);
}
}
}
return 0;
}

