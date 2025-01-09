#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

void display_prompt_and_read_input(char **buffer, size_t *buffer_size);
int tokenize_input(char *buffer, char **memory);
void handle_internal_commands(char **memory, int count);
void execute_external_commands(char **memory, char *buffer);
void free_memory(char **memory, int count);

#endif

