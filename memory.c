#include "shell.h"

/**
 * free_memory - Libère la mémoire allouée pour les tokens
 * @memory: tableau de tokens
 * @count: nombre de tokens
 */
void free_memory(char **memory, int count)
{
    int i;

    for (i = 0; i < count; i++)
    {
        free(memory[i]);
    }
    free(memory);
}

