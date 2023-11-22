#include "shell.h"

/**
 * stok_delim - seperates a string into words using multiple delim
 * @str: string to tokenize
 * @delim: A string of delimiterrs
 * Return: An array of strings (Success), NULL (failed)
 */
char *stok_delim(char *str, char *delim)
{
	static char *tok;

	char *token;

	if (str != NULL)
		tok = str;

	if (tok == NULL)
		return (NULL);
	while (*tok != '\0' && delim_checker(delim, *tok))
		tok++;

	if (*tok == '\0')
		return (NULL);

	token = tok;
	while (tok != '\0' && !delim_checker(delim, *tok))
		tok++;

	if (*tok != '\0')
		*tok++ = '\0';

	return (token);
}

/**
 * delim_checker - checks if a character is a delimiter
 * @str: string to inspect
 * @delim: delimiter
 * Return: 1 (Success), 0 (No match)
 */
char *delim_checker(char *str, int delim)
{
	while (*str != '\0')
	{
		if (*string == delim)
			return (str);
		str++;
	}
	return (NULL);
}

/**
 * shell_getchar - Reads a character from stdin
 * Return: The character read
 */
int shell_getchar(void)
{
	char sh;

	if (read(0, &ch, 1) == 1)
		return ((int)ch);
	else
		return (EOF);
}


