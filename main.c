#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * execute_command - Executes a command in a child process.
 * @cmd: Command to execute.
 * @prog_name: Name of the shell program (argv[0]).
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
	} else
	{


		waitpid(pid, NULL, 0);
	}
}

/**
 * handle_error - Handles errors by printing the program and error message.
 * @prog_name: The program name (argv[0]).
 * @cmd: The command that caused the error.
 */
void handle_error(char *prog_name, char *cmd)
{
	fprintf(stderr, "%s: 1: %s: not found\n", prog_name, cmd);
}

/**
 * main - Entry point of the shell program.
 * @argc: Argument count (not used).
 * @argv: Argument vector (used to get the program name).
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
			printf(":) ");

		nread = getline(&cmd, &len, stdin);
		if (nread == -1)
		{
			free(cmd);
			exit(0);
		}

		cmd[strcspn(cmd, "\n")] = '\0';

		if (strlen(cmd) > 0)
		{
			execute_command(cmd, argv[0]);
		}
	}

	free(cmd);
	return (0);
}

