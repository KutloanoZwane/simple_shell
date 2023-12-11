#include "shell.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>

#define MAX_COMMAND_LENGTH 50
#define MAX_ARGUMENTS 10

/**
 * user_prompt - Displays the shell prompt for user input.
 *
 * This function prints the shell prompt "#" and flushes the output buffer.
 * Parameters: None
 * Returns: None
 */

void user_prompt(void)
{
    printf("# ");
    fflush(stdout);
}

/**
 * main - Entry point of the program.
 *
 * Reads user input, executes commands, and manages the shell.
 * Return: 0 on successful execution.
 */

int main(void)
{
    char command[MAX_COMMAND_LENGTH];
    int length = strlen(command);
    pid_t process_id = fork();

    while (1)
    {
        user_prompt();

        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
        {
            if (feof(stdin))
            {
                printf("\n");
                break;
            }
        }

        if (length > 0 && command[length - 1] == '\n')
        {
            command[length - 1] = '\0';
        }

        if (process_id == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (process_id == 0)
        {
            char *args[MAX_ARGUMENTS];
            char *token = strtok(command, " ");

            int arg_count = 0;
            while (token != NULL && arg_count < MAX_ARGUMENTS - 1)
            {
                args[arg_count] = token;
                token = strtok(NULL, " ");
                arg_count++;
            }

            args[arg_count] = NULL;

            if (execvp(args[0], args) == -1)
            {
                perror("execvp");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            int status;
            waitpid(process_id, &status, 0);
        }
    }

    return 0;
}
