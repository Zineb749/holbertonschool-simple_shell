#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

#define BUFFER_SIZE 1024

void display_prompt_and_read_input(char **buffer, size_t *buffer_size) {
	printf("simple_shell$ ");
	if (getline(buffer, buffer_size, stdin) == -1) {
		free(*buffer);
		exit(EXIT_SUCCESS);
	}
}

int tokenize_input(char *buffer, char **memory) {
	int i = 0;
	int j;
	char *token;

	token = strtok(buffer, " \t\n");
	if (token == NULL) {
		return (0);
	}

	while (token != NULL) {
		memory[i] = malloc(strlen(token) + 1);
		if (memory[i] == NULL) {
			perror("malloc failed");
			for (j = 0; j < i; j++) {
				free(memory[j]);
			}
			return (-1);
		}
		strcpy(memory[i], token);
		token = strtok(NULL, " \t\n");
		i++;
	}
	memory[i] = NULL;
	return (i);
}

void execute_external_commands(char **memory) {
	pid_t child_pid;
	int status;
	int is_piped_input = isatty(fileno(stdin)) == 0;

	child_pid = fork();
	if (child_pid == -1) {
		perror("fork failed");
		return;
	}
	if (child_pid == 0) {
		if (is_piped_input) {
			if (execvp(memory[0], memory) == -1) {
				perror("ERROR execvp:");
				exit(EXIT_FAILURE);
			}
		} else {
			if (execvp(memory[0], memory) == -1) {
				perror("ERROR execvp:");
				exit(EXIT_FAILURE);
			}
		}
	} else {
		wait(&status);
	}
}

void free_memory(char **memory, int count) {
	int i;

	for (i = 0; i < count; i++) {
		free(memory[i]);
	}
}

int main(void) {
	char *buffer = NULL;
	size_t buffer_size = 0;
	char **memory;
	int i;

	memory = malloc(sizeof(char *) * BUFFER_SIZE);
	if (memory == NULL) {
		perror("malloc failed");
		return (EXIT_FAILURE);
	}

	while (1) {
		display_prompt_and_read_input(&buffer, &buffer_size);

		i = tokenize_input(buffer, memory);
		if (i == -1) {
			continue;
		}

		if (i > 0) {
			execute_external_commands(memory);
		}

		free_memory(memory, i);
	}

	free(buffer);
	free(memory);
	return (0);
}

