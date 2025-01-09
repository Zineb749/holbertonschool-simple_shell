#include "shell.h"

/**
 * handle_internal_commands - Gère les commandes internes (exit, env)
 * @memory: tableau de tokens
 * @count: nombre de tokens
 */
void handle_internal_commands(char **memory, int count)
{
    int i;

    if (strcmp(memory[0], "exit") == 0)
    {
        for (i = 0; i < count; i++)
        {
            free(memory[i]);
        }
        free(memory);
        exit(EXIT_SUCCESS);
    }
    else if (strcmp(memory[0], "env") == 0)
    {
        char **env_ptr = environ;
        while (*env_ptr != NULL)
        {
            printf("%s\n", *env_ptr);
            env_ptr++;
        }
    }
}

