#ifndef SHELL_H
#define SHELL_H

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>


#define  MAX_COMMAND_LENGHT 50
#define MAX_ARGS 20
#define MAX_PATH_LENGTH 100

extern char **environ;
void prompt(char *nameShell);
void tokenizeCmd(char *cmd, char *argv[], int *argc);
void execCmd(char *cmd, char *argv[], char *path);
void printEnv(void);
void execAbsoluteCmd(char *cmd, char *argv[]);
void execCmdInPath(char *cmd, char *argv[], char *path);
void executeCommand(char *command);
void handleExitCommand(char *command);
void handleEnvCommand(char *command);

#endif
