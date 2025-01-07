#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

/**
 * print_prompt - Prints the shell prompt.
 */
void print_prompt(void)
{
	write(STDOUT_FILENO, ":) ", 3);
}

/**
 * read_input - Reads user input from stdin.
 * @n: Pointer to the size of the input buffer.
 *
 * Return: A pointer to the buffer containing the input, or NULL on EOF.
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
 * parse_input - Parses the input into an array of tokens.
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
 * execute_command - Executes a command using fork and execve.
 * @array: The array of command arguments.
 */
void execute_command(char **array)
{
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error creating child process");
		free(array[0]);
		free(array);
		exit(1);
	}

	if (child_pid == 0)
	{
		extern char **environ;

		if (execve(array[0], array, environ) == -1)
		{
			perror("Command not found");
			free(array[0]);
			free(array);
			exit(127);
		}
	}
	else
	{
		int status;
		wait(&status);
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

		if (strlen(buf) == 0)
		{
			free(buf);
			continue;
		}

		char **array = parse_input(buf);

		execute_command(array);

		free(array[0]);
		free(array);
	}

	return (0);
}

