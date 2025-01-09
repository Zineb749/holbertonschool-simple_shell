#include "shell.h"

/**
 * display_prompt_and_read_input - Affiche le prompt et lit l'entré
 * @buffer: pointeur vers le buffer de stockage de l'entrée
 * @buffer_size: pointeur vers la taille du buffer
 */
void display_prompt_and_read_input(char **buffer, size_t *buffer_size)
{
	printf("simple_shell$ ");
	if (getline(buffer, buffer_size, stdin) == -1)
	{
		exit(EXIT_SUCCESS);
	}
}
