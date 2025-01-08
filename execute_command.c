#include "main.h"

void execute_command(char **array)
{
    char *command = array[0];
    char *command_path = find_command_in_path(command);

    if (command_path == NULL)
    {
        print_error(array[0], command);
        free(array[0]);
        free(array);
        return;
    }

    fork_and_execute(array, command_path);
}

