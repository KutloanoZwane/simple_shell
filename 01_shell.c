#include <shell.h>

#define  MAX_COMMAND_LENGHT 100

/**
 * user_prompt: prints out the shell prompt for user to enter command.
 * fflush(): Flush the output buffer to display the prompt immediately.
 * return: NULL.
 */

void user_prompt(void)
{
	char prompt[] = "$ ";

	write(STDOUT_FILENO, prompt, sizeof(promp) - 1);
	fflush(stdout);
}

/**
 * main: entry point for the program.
 * command : character array that stores the command entered by the user.
 * fgets() : Reads the command entered by the user from standard input.
 * lenght : lenght of the user command input
 * process_id : child process.
 * argc : array with the command and a NULL terminator.
 * eden : array as the environment variable array.
 * stats: status information of the child process.
 * return : NULL
 */
int main(void)
{
	char command[MAX_COMMAND_LENGHT];

	while (1)
	{
		user_prompt();

		if (fgets(command, MAX_COMMAND_LENGHT, stdin) == NULL)
		{
			if (feof(stdout))
			{
				printf("\n");
				break;
			}
		}

		int lenght = strlen(command);

		if (lenght > 0 && command[lenght - 1] == '\n')
		{
			command[lenght - 1] = '\0';
		}

		pid_t process_id = fork();

		if (process_id == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
	}

	return (0);
}
