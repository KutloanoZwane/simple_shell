#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 50
#define MAX_ARGS 20

/**
 * command - user input command
 * argu - For command, arguments, and NULL terminator
 * process_id - child process
 * return - 0
 */

int main(void)
{
	char command[MAX_COMMAND_LENGTH];
	char *argu[MAX_ARGS + 1];
	char *dtoken = strtok(command, " ");
	int argCount = 0;
	pid_t process_id = fork();

	while (1)
	{
		printf("myshell$ ");
		fflush(stdout);

		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			printf("\n");
			break;
		}

		command[strcspn(command, "\n")] = '\0';

		if (strlen(command) == 0)
		{
			continue;
		}

		while (dtoken != NULL && argCount < MAX_ARGS)
		{
			argu[argCount] = dtoken;
			dtoken = strtok(NULL, " ");
			argCount++;
		}
		argu[argCount] = NULL;
		
		if (process_id < 0)
		{
			perror("Fork failed");
			exit(EXIT_FAILURE);
		}
		else if (process_id == 0)
		{
			if (execve(argu[0], argu, NULL) == -1)
			{
				perror("Execution failed");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			int stats;
			waitpid(process_id, &stats, 0);

			if (WIFEXITED(stats))
			{
				int exitStats = WEXITSTATUS(stats);
				if (exitStats != 0)
				{
					perror("Command failed");
				}
				else
				{
					perror("Command terminated abnormally");
				}
			}
		}
	}

	return 0;
}

