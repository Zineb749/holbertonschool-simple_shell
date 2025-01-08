#include "main.h"

char *find_command_in_path(const char *command)
{
	char *path_env = getenv("PATH");
	char *path = strtok(path_env, ":");
	char *full_path;

	while (path != NULL)
	{
		full_path = malloc(strlen(path) + strlen(command) + 2);
		if (!full_path)
		{
			perror("malloc failed");
			exit(1);
		}

		strcpy(full_path, path);
		strcat(full_path, "/");
		strcat(full_path, command);

		if (access(full_path, X_OK) == 0)
		{
			return full_path;
		}

		free(full_path);
		path = strtok(NULL, ":");
	}

	return NULL;
}

