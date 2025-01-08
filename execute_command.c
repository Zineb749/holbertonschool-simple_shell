#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
/**
 * execute_command - Executes a command in a child process.
 * @cmd: The command to be executed.
 *
 * This function creates a child process using fork(). The child process
 * attempts to execute the specified command using execve(). If execve()
 * fails, an error message is displayed. The parent process waits for the
 * child process to complete using waitpid().
 */

void execute_command(char *cmd)
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
			perror("./hsh");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
}
