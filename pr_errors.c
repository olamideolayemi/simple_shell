#include "shell.h"

/**
 * _eputs - prints an input string
 * @str: string to be printed
 * Return: Nothing
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - writes the declared char to the standarderror
 * @c: Char to be printed
 * Return: 1 (Success)
 */
int _eputchar(char c)
{
	static int i;
	static char buf[BUFFER_SIZE];

	if (c == BUFFER_FLUSH || i >= BUFFER_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putsfd - prints a string into a file
 * @str: string to be printed
 * @fd: file desc to write to
 * Return: number of charcaters printed
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}

/**
 * _putfd - writes the char declared to the given file desc
 * @c: character to print
 * @fd: filedescriptor to write to
 * Return: 1 (Success), -1 ( Error occurs)
 */
int _putfd(char c, int fd)
{
	static int i;
	stattic char buf[BUFFER_SIZE];

	if (c == BUFFER_FLUSH || >= BUFFER_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _erratoi - converts string to integer
 * @s: string to be converted
 * Return: 0 (Number is string), -1 (Error: converted number is not str)
 */
int _erratoi(char *s)
{
	int i = 0;
	unsigned long int res = 0;

	if (*s == '+')
		s++;
	
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			res *= 10;
			res += (s[i] - '0');

			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}
