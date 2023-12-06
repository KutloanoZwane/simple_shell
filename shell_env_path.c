#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 50
#define MAX_PATH_LENGTH 100

/**
 * user_prompt - Displays the shell prompt for user input.
 *
 * This function prints the shell prompt "#" and flushes the output buffer.
 * Parameters: None
 * Returns: None
 */

void user_prompt()
{
	printf("$ ");
	fflush(stdout);
}

/**
 * main - Entry point of the program.
 *
 * Reads user input, executes commands, and manages the shell.
 * Return: 0 on successful execution.
 */

int main()
{
	char command[MAX_COMMAND_LENGTH];
	char path[MAX_PATH_LENGTH];

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

		char *eden_path = getenv("PATH");
		
		if (eden_path == NULL)
		{
			perror("Error: PATH environment variable not found");
			continue;
		}

		char *tokenPath = strtok(eden_path, ":");
		
		int cmd_found = 0;

		while (tokenPath != NULL)
		{
			snprintf(path, MAX_PATH_LENGTH, "%s/%s", tokenPath, command);
			if (access(path, X_OK) == 0)
			{
				cmd_found = 1;
				break;
			}
			tokenPath = strtok(NULL, ":");
		}

		if (!cmd_found)
		{
			perror("Error: Command not found");
			continue;
		}
		
		pid_t process_id = fork();
		
		if (process_id == -1)
		{
			perror("Error: Fork failed");
			exit(EXIT_FAILURE);
		}
		else if (process_id == 0)
		{
			char *argu[] = {command, NULL};
			char *eden[] = {NULL};

			if (execve(command, argu, eden) == -1)
			{
				perror("Error: Execve failed");
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
