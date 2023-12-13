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
/**
 * printEnv - Function that displays the environment variables
 * Parameters: 0.
 *
 * Returns: Always 0.
 */
void printEnv(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}
/**
 * tokenizeCmd - function that takes a command string and,
 * splits it into pieces.
 * @cmd: part of the command string to be split(tokenized)
 * @argv: the array to store the command tokens.
 * @argc: a storage for the number of command tokens
 */
void tokenizeCmd(char *cmd, char *argv[], int *argc)
{
	char delimiter[] = " ;";
	char *token;
	*argc = 0;

	while ((token = strsep(&cmd, delimiter)) != NULL)
	{
		if (*token != '\0')
		{
			argv[(*argc)++] = token;
			if (*argc >= MAX_ARGUMENTS - 1)
			{
				break;
			}
		}
	}

	argv[*argc] = NULL;
}
/**
 * execCmd - execCmd executes a command
 * @cmd: user cmd to be executed
 * @argv: Array of cmd line argument
 * @path: Directories in PATH environment
 *
 */
void execCmd(char *cmd, char *argv[], char *path)
{
	if (cmd != NULL && argv != NULL)
	{
		(cmd[0] == '/' || cmd[0] == '.') ?
			execAbsoluteCmd(cmd, argv) :
			execCmdInPath(cmd, argv, path);
	}
}
