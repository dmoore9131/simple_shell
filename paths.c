#include "shell.h"

/**
 * *_getenv - in the environment variables key-value pairs
 *					are stored, amd _getenv just like "getenv"
 *					gets the value of a given environment variable
 *
 * @name: the name of the environment variable
 *
 * Return: c string (value)
*/

char *_getenv(const char *name)
{
	int i, is_the_path;
	char *value;

	for (i = 0; environ[i]; i++)
	{
		value = strtok(environ[i], "=");

		is_the_path = strcmp(value, name);

		if (!is_the_path)
		{
			return (strtok(NULL, "\n"));
		}
	}

	return (NULL);
}

/**
 * file_exits - checks if file exists in the
 *							PATH env
 *
 * @name: name of the file
 *
 * Return: byte 0 success, 1 failure
*/

file_status *file_exists(char *name)
{
	char *paths, *directory, *file;
	struct stat st;
	file_status *f_stat;

	f_stat = malloc(sizeof(char) + BUFFER);
	paths = _getenv("PATH");

	/* first directory in paths */
	directory =  strtok(paths, ":");

	file = concatenate(3, directory, "/", name);

	if (!stat(file, &st))
	{
		f_stat->found = 0;
		f_stat->path = file;

		return (f_stat);
	}

	while (directory)
	{
		directory = strtok(NULL, " :\n");
		if (!stat(directory, &st))
		{
			file = concatenate(3, directory, "/", name);

			if (!stat(file, &st))
			{
				f_stat->found = 0;
				f_stat->path = file;

				return (f_stat);
			}
		}
	}

	f_stat->found = 1;
	return (f_stat);
}

/**
 * execute_command - using execve it executes a file in your environment
 *
 * @tokens: tokens that build up the command i,e ["ls", "-al"]
 *
 * Return void
*/

void execute_command(char **tokens)
{
	pid_t execve_pid;

	execve_pid = fork();

	if (execve_pid == -1)
		perror("execve error");

	if (execve_pid == 0)
	{
		int exec_error;

		exec_error = execve(tokens[0], tokens, NULL);
		if (exec_error == -1)
			printf("%s does not exist\n", tokens[0]);
	}

	wait(&execve_pid);
	printf("$ ");
}

