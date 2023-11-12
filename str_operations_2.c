#include "shell.h"

/**
 * _putchar - writes character c to stdout
 * @c: character to print
 * Return: 1 (success), -1 (error)
 */
int _putchar(char c)
{
	static int i;
	static char buf[READ_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || i >= READ_BUFFER_SIZE)
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
	int i = 0;

	if (dst == src || src == NULL)
		return (dst);

	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';

	return (dst);
}

/**
 * dup_str - duplicates string
 * @str: string to be duplicated
 * Return: pointer to duplicated string
 */
char *dup_str(const char *str)
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
