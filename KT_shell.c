#include "shell.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_COMMAND_LENGTH 100

/**
 * prompt - should display the shell prompt and
 * handle user commands.
 * @NameofShell: Name of the Shell.
 *
 * Return: Always
 */
void handleExit(void)
{
	printf("Exiting the shell...\n");
	exit(EXIT_SUCCESS);
}

void handleEnv(void)
{
	extern char **environ;
	printf("Environment variables:\n");
	for (int k = 0; environ[k] != NULL; k++)
	{
		printf("%s\n", environ[k]);
	}
}

void executeCommand(char *command) {
    int status = system(command);

    if (status == -1) {
        perror("Command execution failed");
    }
}

void prompt(char *nameofShell) {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        if (isatty(STDIN_FILENO)) {
            printf("%s## ", nameofShell);
            fflush(stdout);
        }

        if (fgets(command, sizeof(command), stdin) == NULL) {
            break;
        }

        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "exit") == 0) {
            handleExit();
            break;
        }

        if (strcmp(command, "env") == 0) {
            handleEnv();
            continue;
        }

        executeCommand(command);
    }
}
