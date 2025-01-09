#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

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
 * This function reads a line of input from the user and returns it.
 * If reading fails or EOF is encountered, it will exit the program.
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
 * This function splits the input string into tokens based on whitespace
 * and stores them in an array.
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
 * execute_command - Executes the command using fork and execve system call.
 * @array: The array of command arguments.
 * @program_name: The name of the program (argv[0]).
 *
 * This function forks a child process and uses execve to execute the command.
 * If execution fails, an error message is printed.
 */
void execute_command(char **array, char *program_name)
{
	pid_t child_pid;
	int status;

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error creating child process");
		free(array[0]);
		free(array);
		exit(1);
	}

	if (child_pid == 0)
	{
		if (access(array[0], X_OK) == -1)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", program_name, array[0]);
			free(array[0]);
			free(array);
			exit(127);
		}
		if (execve(array[0], array, environ) == -1)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", program_name, array[0]);
			free(array[0]);
			free(array);
			exit(127);
		}
	}
	else
	{
		wait(&status);
	}
}

/**
 * main - Main entry point for the shell program.
 * It prints the prompt, reads user input, parses it, and executes the command.
 * @argc: Argument count.
 * @argv: Argument vector.
 *
 * Return: 0 on successful execution.
 * This function continuously loops, displaying the prompt, reading the user's
 * input, and executing the command. If the user provides an empty input or
 * if an error occurs, the loop continues.
 */
int main(int argc, char *argv[])
{
	size_t n;
	char *buf;
	char **array;

	(void)argc;

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
		execute_command(array, argv[0]);
		free(array[0]);
		free(array);
	}

	return (0);
}

