#include "shell.h"

void display_prompt_and_read_input(char **buffer, size_t *buffer_size)
{
	printf("simple_shell$ ");
	if (getline(buffer, buffer_size, stdin) == -1)
	{
		exit(EXIT_SUCCESS);
	}
}

int tokenize_input(char *buffer, char **memory)
{
	int i = 0;
	char *token;

	token = strtok(buffer, " \t\n");
	if (token == NULL)
	{
		return (0);
	}

	while (token != NULL)
	{
		memory[i] = malloc(strlen(token) + 1);
		if (memory[i] == NULL)
		{
			perror("malloc failed");
			return (-1);
		}
		strcpy(memory[i], token);
		token = strtok(NULL, " \t\n");
		i++;
	}
	memory[i] = NULL;
	return (i);
}

void handle_internal_commands(char **memory, int count)
{
	int i;

	if (strcmp(memory[0], "exit") == 0)
	{
		for (i = 0; i < count; i++)
		{
			free(memory[i]);
		}
		free(memory);
		exit(EXIT_SUCCESS);
	}
	else if (strcmp(memory[0], "env") == 0)
	{
		char **env_ptr = environ;
		while (*env_ptr != NULL)
		{
			printf("%s\n", *env_ptr);
			env_ptr++;
		}
	}
}

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

void free_memory(char **memory, int count)
{
	int i;

	for (i = 0; i < count; i++)
	{
		free(memory[i]);
	}
	free(memory);
}

int main(void)
{
	char *buffer = NULL;
	size_t buffer_size = 0;
	char **memory;
	int i;

	memory = malloc(sizeof(char *) * 1024);
	if (memory == NULL)
	{
		perror("malloc failed");
		return (EXIT_FAILURE);
	}

	while (1)
	{
		display_prompt_and_read_input(&buffer, &buffer_size);

		i = tokenize_input(buffer, memory);
		if (i == -1)
		{
			continue;
		}

		if (i > 0 && (strcmp(memory[0], "exit") == 0 || strcmp(memory[0], "env") == 0))
		{
			handle_internal_commands(memory, i);
		}
		else if (i > 0)
		{
			execute_external_commands(memory, buffer);
		}

		free_memory(memory, i);
	}

	free(buffer);
	return (0);
}

