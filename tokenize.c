#include "shell.h"

/**
 * tokenize_input - Analyse l'entrée en tokens
 * @buffer: buffer contenant l'entrée de l'utilisateur
 * @memory: tableau pour stocker les tokens
 * 
 * Return: le nombre de tokens ou -1 en cas d'erreur
 */
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
