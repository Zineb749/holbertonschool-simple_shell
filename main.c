#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * execute_command - Executes a command in a child process.
 * @cmd: Command to execute.
 * @prog_name: Shell program's name (argv[0]).
 *
 * If execution fails, prints an error using prog_name.
 */
void execute_command(char *cmd, char *prog_name)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		char *args[2];

		args[0] = cmd;
		args[1] = NULL;

		if (execve(cmd, args, NULL) == -1)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", prog_name, cmd);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
}

/**
 * main - Entry point of the shell.
 * @argc: Argument count.
 * @argv: Argument vector.
 *
 * Reads commands from input, executes them, and prints errors if needed.
 * Return: 0.
 */

int main(int argc, char **argv)
{
	char *cmd = NULL;
	size_t len = 0;
	ssize_t nread;

	(void)argc;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf(":] ");

		nread = getline(&cmd, &len, stdin);
		if (nread == -1)
		{
			free(cmd);
			exit(0);
		}

		cmd[strcspn(cmd, "\n")] = '\0';

		if (strlen(cmd) > 0)
			execute_command(cmd, argv[0]);
	}

	free(cmd);
	return (0);
}

