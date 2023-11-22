#include "shell.h"

/**
 * main - main function
 * @argc: pointer to argument count
 * @argv: pointer to argument vector
 * Return: 0 (success)
 */
int main(int argc, char **argv)
{
	(void)argc;
	return (shell_loop(argv));
}

init main
