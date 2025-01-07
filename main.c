#include "main.h"

int main(int argc, char *argv[])
{
	(void)argc, (void)argv;

	size_t n = 0;
	char *buf = NULL;
	ssize_t nread;
	pid_t child_pid;
	int status;
	char **array;
	int i;
	char *token;

	while (1)
	{
		write(STDOUT_FILENO, ":)", 2);

		nread = getline(&buf, &n, stdin);

		if (nread == -1)
		{
			perror("Exiting shell");
			free(buf);
			exit(1);
		}

		token = strtok(buf, "\n");

		array = malloc(sizeof(char *) * 1000);
		if (!array)
		{
			perror("Memory allocation failed");
			free(buf);
			exit(1);
		}

		i = 0;
		while (token)
		{
			array[i] = token;
			token = strtok(NULL, "\n");
			i++;
		}
		array[i] = NULL;

		child_pid = fork();

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
			wait(&status);
			free(array);
		}
	}

	free(buf);

	return (0);
}

