/**
* _getline - read a line from the user prompt.
* @data: struct the program data
*
* Return: continue reading counting bytes.
*/
int _getline(data_of_program *data)
{
	char buff[BUFFER_SIZE] = {'\0'};
	static char *array_commands[10] = {NULL};
	static char array_operators[10] = {'\0'};
	ssize_t bytes_read, i = 0;

	if (!array_commands[0] || (array_operators[0] == '&' && errno != 0) ||
			(array_operators[0] == '|' && errno == 0))
	{
		for (i = 0; array_commands[i]; i++)
		{
			free(array_commands[i]);
			array_commands[i] = NULL;
		}

		bytes_read = read(data->file_descriptor, &buff, BUFFER_SIZE - 1);
		if (bytes_read == 0)
			return (-1);

		i = 0;
		do
		{
			array_commands[i] = str_duplicate(_strtok(i ? NULL : buff, "\n;"));

			i = check_logic_ops(array_commands, i, array_operators);
		}
		while (array_commands[i++]);
	}

	data->input_line = array_commands[0];
	for (i = 0; array_commands[i]; i++)
	{
		array_commands[i] = array_commands[i + 1];
		array_operators[i] = array_operators[i + 1];
	}

	return (str_length(data->input_line));
}


/**
* check_logic_ops - checks and split certain operators
* @array_commands: command array
* @i: index to be checked
* @array_operators: logical operators array of commands
*
* Return: index of the command.
*/
int check_logic_ops(char *array_commands[], int i, char array_operators[])
{
	char *temp = NULL;
	int j;

	for (j = 0; array_commands[i] != NULL  && array_commands[i][j]; j++)
	{
		if (array_commands[i][j] == '&' && array_commands[i][j + 1] == '&')
		{

			temp = array_commands[i];
			array_commands[i][j] = '\0';
			array_commands[i] = str_duplicate(array_commands[i]);
			array_commands[i + 1] = str_duplicate(temp + j + 2);
			i++;
			array_operators[i] = '&';
			free(temp);
			j = 0;
		}
		if (array_commands[i][j] == '|' && array_commands[i][j + 1] == '|')
		{

			temp = array_commands[i];
			array_commands[i][j] = '\0';
			array_commands[i] = str_duplicate(array_commands[i]);
			array_commands[i + 1] = str_duplicate(temp + j + 2);
			i++;
			array_operators[i] = '|';
			free(temp);
			j = 0;
		}
	}
	return (i);
}

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
	}
	argv[*argc] = NULL;
}
