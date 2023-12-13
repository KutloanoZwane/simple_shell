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
 * handleExitCommand - function that exit a command
 * @command: command
 *
 * Return: Always
 */
void handleExitCommand(char *command)
{
	if (strcmp(command, "exit") == 0
			{
			exit(EXIT_SUCCESS);
			}
}
/**
 * handleEnvCommand - function that exit a command
 * @command: command
 *
 * Return: Always
 */
void handleEnvCommand(char *command)
{
if (strcmp(command, "env") == 0)
{
printEnv();
}
}
