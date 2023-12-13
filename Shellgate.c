#include "shell.h"

/**
 * main - shell program that prints
 * the a prompt with the name of the shell.
 *
 * Return: Always 0.
 */
int main(void)
{
        char *nameofShell = "KT_shell";

        prompt(nameofShell);
        return (0);
}
