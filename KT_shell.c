#include "shell.h"
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 20

/**
 * prompt - should display the shell prompt and
 * handle user commands.
 * @nameofShell: Name of the Shell.
 *
 * Return: Always
 */
void prompt(char *nameofShell)
{
	char command[MAX_COMMAND_LENGTH];
	char *argv[MAX_ARGUMENTS];
	char *path = getenv("PATH");
	int argc;
	pid_t child_id;
	int status;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			printf("%s## ", nameofShell);
			fflush(stdout);
		}
		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			break;
		}
		command[strcspn(command, "\n")] = '\0';
		handleExitCommand(command);
		handleEnvCommand(command);
		tokenizeCmd(command, argv, &argc);
		execCmd(argv[0], argv, path);
	}
}
