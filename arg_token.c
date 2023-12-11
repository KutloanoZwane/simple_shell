#include "shell.h"
#include <string.h>
#include <stdlib.h>

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
			if (*argc >= MAX_ARGS - 1)
			{
				break;
			}

		}
		argv[*argc] = NULL;
}
