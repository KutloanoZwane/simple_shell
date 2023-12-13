#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include <unistd.h>

/**
 * printEnv - Function that displays the environment variables
 * Parameters: 0.
 *
 * Returns: Always 0.
 */
void printEnv(void)
{
char **env = environ;

do {
printf("%s\n", *env);
env++;
} while (*env != NULL);
}
