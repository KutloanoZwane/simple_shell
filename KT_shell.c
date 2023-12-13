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
 * @NameofShell: Name of the Shell.
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
/* Remove the trailing newline from the command */
command[strcspn(command, "\n")] = '\0';
/*  Exit Handling */
if (strcmp(command, "exit") == 0)
{
break;
}
if (strcmp(command, "env") == 0)
{
printEnv();
continue;
}
/* Tokenize the command into arguments */
tokenizeCmd(command, argv, &argc);
/* Execute the command */
child_id = fork();
if (child_id == -1)
{
perror("fork");
continue;
}
else if (child_id == 0)
{
execCmd(argv[0], argv, path);
exit(EXIT_FAILURE);
}
else
{
waitpid(child_id, &status, 0);
if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
{
continue;
}
}
}
}
