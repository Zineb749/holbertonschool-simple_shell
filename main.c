#include "main.h"

/**
 * print_prompt - Prints the shell prompt ":) " to STDOUT.
 * This function is responsible for displaying a simple prompt to the user
 * before waiting for the next command input.
 */
void print_prompt(void)
{
	write(STDOUT_FILENO, ":) ", 3);
}

/**
 * read_input - Reads user input from stdin.
 * @n: Pointer to the size of the input buffer.
 *
 * Return: A pointer to the buffer containing the user input.
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
 * parse_input - Parses the input buffer into an array of tokens.
 * @buf: The input buffer to tokenize.
 *
 * Return: An array of strings (tokens).
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
	array[0] = buf;
	array[1] = NULL;

	return (array);
}

/**
 * main - Main entry point for the shell program.
 * It prints the prompt, reads user input, parses it, and executes the command.
 * @argc: Argument count.
 * @argv: Argument vector.
 *
 * Return: 0 on successful execution.
 */
int main(int argc, char *argv[])
{
	size_t n;
	char *buf;
	char **array;

	(void)argc;
	(void)argv;

	while (1)
	{
		print_prompt();

		buf = read_input(&n);

		if (strlen(buf) == 0)
		{
			free(buf);
			continue;
		}

		array = parse_input(buf);

		execute_command(array);

		free(array[0]);
		free(array);
	}

	return (0);
}

