#include "main.h"

void fork_and_execute(char **array, const char *command_path)
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
		if (execve(command_path, array, NULL) == -1)
		{
			perror("execve failed");
			free(array[0]);
			free(array);
			free((char *)command_path);
			exit(127);
		}
	}
	else
	{
		int status;
		wait(&status);
		free((char *)command_path);
	}
}

