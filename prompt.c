#include "main.h"
/**
 * print_prompt - Displays a simple prompt to the user.
 *
 * Prints ":) " to the standard output to prompt the user for input.
 */

void print_prompt(void)
{
	write(STDOUT_FILENO, ":) ", 3);
}

