#include "shell.h"

/**
 * _chdir - modifies the working directory of the process
 * @info: struct containing arguments
 * Return: Always 0
 */
int _chdir(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_res;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("PROMPT: ** getcwd failure msg **");

	if (!info->argv[1])
	{
		dir = _getenv(info, "Home=");
		if (!dir)
			chdir_res =
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_res = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_res =
			chdir((dir = _getenv(info, "OLDPWD=")) ? : "/");
	}
	else
	{
		chdir_res = chdir(info->argv[1]);
	}

	if (chdir_res == -1)
	{
		print_error(info, "cannot change dir to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _shellexit - terminates shell processes
 * @info: struct containing potential arguments
 * Return: 0
 */
int _shellexit(info_t *info)
{
	int exit_code;

	if (info->argv[1])
	{
		exit_code = _erratoi(info->argv[1]);
		if (exit_code == -1)
		{
			info->status = 2;
			print_error(info, "Unrecognized Number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _showhelp - displays help information
 * @info: structure containing potential arguments
 * Return: Always 0
 */
int _showhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("The help function was invoked. Function is not yet operational.\n");
	if (0)
		_puts(*arg_array);
	return (0);
}

/**
 * _showhistory - displays command history with line numbers
 * @info: struct containing potential arguments
 * Return: Always 0
 */
int _showhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - Removes an alias
 * @info: parameter struct
 * @str: alias to be unset
 * Return: Always 0 (Success)
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int res;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	res = delete_node_at_index(&(info->alias),
			get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;

	return (res);
}
