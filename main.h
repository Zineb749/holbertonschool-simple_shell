#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void print_prompt(void);
char *read_input(size_t *n);
char **parse_input(char *buf);
void execute_command(char **array);
char *find_command_in_path(const char *command);
void print_error(const char *program_name, const char *command);
void fork_and_execute(char **array, const char *command_path);

#endif

