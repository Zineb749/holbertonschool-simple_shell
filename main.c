#include "main.h"

/**
 * main - Entry point of the shell program.
 *
 * This function implements a basic shell loop. It displays a prompt reads
 * a command from the user, and passes the command to execute_command(). The
 * loop continues until the user signals EOF (Ctrl+D), at which point the shell
 * exits cleanly.
 *
 * Return: Always 0 on success.
 */

int main(void)
{
	char *cmd = NULL;
	size_t len = 0;
	ssize_t nread;

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
			execute_command(cmd);
	}

	free(cmd);
	return (0);
}

