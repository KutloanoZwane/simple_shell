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

/* Prompt to be printed */
#define PROMPT_MSG "$" /* Needed to work with signal */

/* Resume from the unused attibute */
#define UNUSED _attribute_((unused))

/* buffer size for each read call in _getline */
#define BUFFER_SIZE 1024


typedef struct {
    ino_t readfd;
} info_t;

#define INFO_INIT { 0 } 

/************* STRUCTURES **************/

/**
 * struct info- struct for the program's data
 * @program_name: the name of the executable
 * @input_line: pointer to the input read for _getline
 * @command_name: pointer to the first command typed by the user
 * @exec_counter: number of excecuted comands
 * @file_descriptor: file descriptor to the input of commands
 * @tokens: pointer to array of tokenized input
 * @env: copy of the environ
 * @alias_list: array of pointers with aliases.
 */
typedef struct info
{
	char *program_name;
	char *input_line;
	char *command_name;
	int exec_counter;
	int file_descriptor;
	char **tokens;
	char **env;
	char **alias_list;
} data_of_program;

extern char **environ;
void prompt(char *nameShell);
void tokenizeCmd(char *cmd, char *argv[], int *argc);
void execCmd(char *cmd, char *argv[], char *path);
void printEnv(void);
void execAbsoluteCmd(char *cmd, char *argv[]);
void execCmdInPath(char *cmd, char *argv[], char *path);

int main(int ac, char **av);

int check_logic_ops(char *array_commands[], int i, char array_operators[]);
int _getline(data_of_program *data);

#endif
