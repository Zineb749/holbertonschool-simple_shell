#include "main.h"
/**
 * execute_command - Forks a child process to execute a command.
 * @array: Array of command arguments.
 *
 * Uses `fork` to create a child process and `execve` to execute the command.
 * The parent process waits for the child to finish.
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
		if (execve(array[0], array, NULL) == -1)
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

