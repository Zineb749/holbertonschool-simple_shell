#include <stdio.h>

void print_error(const char *program_name, const char *command)
{
	fprintf(stderr, "%s: 1: %s: not found\n", program_name, command);
}

