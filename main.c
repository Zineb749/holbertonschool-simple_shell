#include "main.h"
/**
 * main - Entry point for the shell program.
 * @argc: Argument count.
 * @argv: Argument vector.
 *
 * Runs an infinite loop, displaying a prompt, reading user input,
 * parsing the input, and executing commands. Exits on user command or error.
 *
 * Return: 0 on success.
 */

int main(int argc, char *argv[])
{
	size_t n;
	char *buf;
	char **array;

	(void)argc;
	(void)argv;

	while (1)
	{
		print_prompt();

		buf = read_input(&n);

		if (strlen(buf) == 0)
		{
			free(buf);
			continue;
		}

		array = parse_input(buf);

		execute_command(array);

		free(array[0]);
		free(array);
	}

	return (0);
}

