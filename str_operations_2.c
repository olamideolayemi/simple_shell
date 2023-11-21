#include "shell.h"

/**
 * _putchar - writes character c to stdout
 * @c: character to print
 * Return: 1 (success), -1 (error)
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buf[i++] = c;

	return (1);
}

/**
 * _strcpy - copiesstring
 * @dst: string destination
 * @src: string source
 * Return: pointer to string destination
 */
char *_strcpy(char *dst, char *src)
{
	int a = 0;

	if (dst == src || src == NULL)
		return (dst);

	while (src[a])
	{
		dst[a] = src[a];
		i++;
	}
	dst[a] = '\0';

	return (dst);
}

/**
 * _dupstr - duplicates string
 * @str: string to be duplicated
 * Return: pointer to duplicated string
 */
char *_dupstr(const char *str)
{
	int len = 0;
	char *res;

	if (str == NULL)
		return (NULL);

	while (*str++)
		len++;

	res = malloc(sizeof(char) * (len + 1));

	if (!res)
		return (NULL);

	for (len++; len--;)
		res[len] = *--str;

	return (res);
}
