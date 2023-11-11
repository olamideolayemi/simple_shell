#include "shell.h"

/**
 * set_alias_cmd - creates or updates an alias
 * @info: struct parameter
 * @str: alias to set
 * Return: Always 0 (Success)
 */
int set_alias_cmd(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alais(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias_cmd - Prints an alias string
 * @node: the alias node
 * Return: Always 0 (success)
 */
int print_alias_cmd(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * manage_alias - manages alias
 * @info: structure containing potential arguments
 * Return: Always 0 (Success)
 */
int manage_alias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias_cmd(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias_cmd(info, info->argv[i]);
		else
			print_alias_cmd(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
