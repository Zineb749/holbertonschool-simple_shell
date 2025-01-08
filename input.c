#include "main.h"
/**
 * read_input - Reads a line of input from stdin.
 * @n: Pointer to the buffer size.
 *
 * Return: A pointer to the input buffer or exits on error.
 */
char *read_input(size_t *n)
{
	char *buf = NULL;
	ssize_t nread = getline(&buf, n, stdin);

	if (nread == -1)
	{
		if (feof(stdin))
		{
			free(buf);
			write(STDOUT_FILENO, "\n", 1);
			exit(0);
		}
		perror("Error reading input");
		free(buf);
		exit(1);
	}

	return (buf);
}

/**
 * parse_input - Tokenizes input into an array of strings.
 * @buf: The input string.
 *
 * Return: A dynamically allocated array.
 */
char **parse_input(char *buf)
{
	char **array = malloc(sizeof(char *) * 2);

	if (!array)
	{
		perror("Memory allocation failed");
		free(buf);
		exit(1);
	}

	buf[strcspn(buf, "\n")] = '\0';

	array[0] = strdup(buf);
	if (!array[0])
	{
		perror("Memory allocation failed");
		free(buf);
		free(array);
		exit(1);
	}

	array[1] = NULL;

	free(buf);

	return (array);
}

