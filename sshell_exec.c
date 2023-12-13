#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * execAbsoluteCmd - function to execute absolute command
 * @cmd: user cmd to be executed
 * @argv: Array of the cmd line arg
 *
 */
void execAbsoluteCmd(char *cmd, char *argv[])
{
if (execve(cmd, argv, environ) != 0)
{
perror("execve");
}
}

/**
 * execCmdInPath -function executes a command in a path
 * @cmd: user cmd to be executed
 * @argv: Array of cmd line argument
 * @path: Directories in the path environments
 */
void execCmdInPath(char *cmd, char *argv[], char *path)
{
char command_path[256] = "";
size_t command_path_length = 0;
int found = 0;
char *dir;

char path_copy[256];
strncpy(path_copy, path, sizeof(path_copy));
path_copy[sizeof(path_copy) - 1] = '\0';

dir = strtok(path_copy, ":");

while (dir != NULL)
{
command_path_length = strlen(dir);
if (command_path_length + 1 + strlen(cmd) < sizeof(command_path))
{
strncpy(command_path, dir, sizeof(command_path) - command_path_length - 1);
strncat(command_path, "/", sizeof(command_path) - strlen(command_path) - 1);
command_path_length += 1;
strncat(command_path, cmd, sizeof(command_path) - command_path_length - 1);
if (execve(command_path, argv, environ) != -1)
{
found = 1;
break;
}
}
else
{
fprintf(stderr, "Command path length exceeded buffer size\n");
break;
}
dir = strtok(NULL, ":");
}

if (!found)
{
  /* fprintf(stderr, "Executable not found: %s\n", command);*/
}
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
