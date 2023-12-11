#ifndef SHELL_H
#define SHELL_H

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

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
<<<<<<< HEAD
int _getline(data_of_program *data);
=======

int check_logic_ops(char *array_commands[], int i, char array_operators[]);
int _getline(data_of_program *data);

>>>>>>> 955bcbe7c2e6119835a7f740457c7f91ffd169e3
void user_prompt(void);
int main(void);

#endif
