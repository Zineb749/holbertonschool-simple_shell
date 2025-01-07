#include "main.h"

/**
 * print_prompt - Prints the shell prompt.
 */
void print_prompt(void)
{
	write(STDOUT_FILENO, ":)", 2);
}

/**
 * read_input - Reads user input from stdin.
 * @n: Pointer to the size of the input buffer.
 *
 * Return: A pointer to the buffer containing the input.
 */
char *read_input(size_t *n)
{
	char *buf = NULL;
	ssize_t nread = getline(&buf, n, stdin);

	if (nread == -1)
	{
		perror("Exiting shell");
		free(buf);
		exit(1);
	}

	return (buf);
}

/**
 * parse_input - Parses the input into an array of tokens.
 * @buf: The input buffer to tokenize.
 *
 * Return: An array of strings (tokens).
 */
char **parse_input(char *buf)
{
	char **array = malloc(sizeof(char *) * 1000);
	char *token;
	int i = 0;

	if (!array)
	{
		perror("Memory allocation failed");
		free(buf);
		exit(1);
	}

	token = strtok(buf, "\n");
	while (token)
	{
		array[i] = token;
		token = strtok(NULL, "\n");
		i++;
	}

	array[i] = NULL;

	return (array);
}

/**
 * execute_command - Executes a command using fork and execve.
 * @array: The array of command arguments.
 * @buf: The input buffer.
 */
void execute_command(char **array, char *buf)
{
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		perror("Child not created.");
		free(array);
		free(buf);
		exit(41);
	}

	if (child_pid == 0)
	{
		if (execve(array[0], array, NULL) == -1)
		{
			perror("Failed to execute");
			free(array);
			free(buf);
			exit(97);
		}
	}
	else
	{
		int status;

		wait(&status);

		free(array);
	}
}

/**
 * main - Main entry point for the shell.
 * @argc: Argument count.
 * @argv: Argument vector.
 *
 * Return: 0 on success.
 */
int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	size_t n = 0;
	char *buf;

	while (1)
	{
		print_prompt();

		buf = read_input(&n);

		char **array = parse_input(buf);

		execute_command(array, buf);

		free(buf);
	}

	return (0);
}

