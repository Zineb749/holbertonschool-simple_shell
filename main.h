#ifndef MAIN_H
#define MAIN_H

#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>


void print_prompt(void);
char *read_input(size_t *n);
char **parse_input(char *buf);
void execute_command(char **array);

#endif

