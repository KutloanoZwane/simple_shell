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
	int argc;
	pid_t pid;
	int status;

	while (1)
	{
		printPrompt(nameofShell);
		if (!getCommand(command, sizeof(command)))
			break;
		if (!strcmp(command, "exit"))
			break;
		tokenizeCmd(command, argv, &argc);
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			continue;
		}
		else if (pid == 0)
			execCmd(argv[0], argv, getEnvPath());

		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			continue;
	}
}
