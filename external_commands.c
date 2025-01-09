#include "shell.h"

/**
 * execute_external_commands - Exécute les commandes externes
 * @memory: tableau de tokens
 * @buffer: buffer contenant l'entrée de l'utilisateur
 */
void execute_external_commands(char **memory, char *buffer)
{
	pid_t child_pid;
	int status;
	int is_piped_input = isatty(fileno(stdin)) == 0;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork failed");
		return;
	}
	if (child_pid == 0)
	{
		if (is_piped_input)
		{
			if (execvp(memory[0], memory) == -1)
			{
				perror("ERROR execvp:");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (execvp(memory[0], memory) == -1)
			{
				perror("ERROR execvp:");
				exit(EXIT_FAILURE);
			}
		}
	}
	else
	{
		wait(&status);
	}
}

