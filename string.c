#include "shell.h"

/**
 * concatenate - join together a number of strings
 *
 * @count: number of strings to be concatenated
 * @...: strings in a varaidac form
 *
 * Return: string which is concatenated
*/

char *concatenate(int count, ...)
{
	va_list args;
	char *buffer, *str;
	int i;

	va_start(args, count);

	buffer = malloc(sizeof(char) * 100024);

	if (buffer == NULL)
		return (NULL);

	for (i = 0; i < count; i++)
	{
		str = va_arg(args, char *);
		strcat(buffer, str);
	}

	va_end(args);

	return (buffer);
}

