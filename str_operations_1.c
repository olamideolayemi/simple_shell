#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @str: string whose length to determine
 * Return: length of the string
 */
int _strlen(char *str)
{
	int len = 0;

	if (!str)
		return (0);

	while (*str++)
		len++;

	return (len);
}

/**
 * starts_with - checks starting of string
 * @hay: string to be searched
 * @ndl: substring to find
 * Return: address of next char
 */
char *starts_with(const char *hay, const char *ndl)
{
	while (*ndl)
	{
		if (*ndl++ != *hay++)
			return (NULL);
	}
	return ((char *)hay);
}

/**
 * _strconcat - concatenates two strings
 * @dst: buffer destination
 * @src: buffer source
 * Return: pointer to buffer destination
 */
char *_strconcat(char *dst, char *src)
{
	char *res = dst;

	while (*dst)
		dst++;

	while (*src)
		*dst++ = *src++;

	*dst = *src;

	return (res);
}

/**
 * _strcmp - compares two strings
 * @str1: first string
 * @str2: the second string
 * Return: Negative (if str1 is less than str2),
 * positive (str1 is greater str2)
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}

	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * _puts - prints string input
 * @str: string to be printed
 * Return: Nothing
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}
