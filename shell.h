#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

void print_prompt(void);
char *read_input(size_t *n);
char **parse_input(char *buf);
void execute_command(char **array, char *program_name);

#endif /* MAIN_H */

