#include "shell.h"

/**
 * main - simple shell
 *
 * Return: 0 (sucessful)
*/


int main(void)
{
	size_t length = BUFFER;
	ssize_t charector_count;
	char *buffer = NULL, **tokens = NULL;

	file_status *f_status;

	printf("$ ");
	while (1)
	{
		charector_count = getline(&buffer, &length, stdin);

		if (charector_count == -1)
		{
			printf("\n");
			return (-1);
		}

		tokens = tokenize(buffer, 0);
		f_status = file_exists(tokens[0]);

		if (f_status->found)
		{
			printf("%s does not exist\n$ ", buffer);
			continue;
		}

		tokens[0] = f_status->path;
		free(f_status);

		execute_command(tokens);
	}

	return (0);
}

