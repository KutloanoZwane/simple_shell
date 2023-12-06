#include "shell.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>

#define  MAX_COMMAND_LENGTH 50

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

		int length = strlen(command);

		if (length > 0 && command[length - 1] == '\n')
		{
			command[length - 1] = '\0';
		}

		pid_t process_id = fork();

		if (process_id == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (process_id == 0)
		{
			char *argu[] = {command, NULL};
			char *eden[] = {NULL};

			if (execve(command, argu, eden) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			int stats;

			waitpid(process_id, &stats, 0);
		}
	}

	return (0);
}
