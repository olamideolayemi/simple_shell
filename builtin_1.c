#include "shell.h"

/**
 * change_dir - modifies the working directory of the process
 * @info: struct containing arguments
 * Return: Always 0
 */
int change_dir(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_res;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("PROMPT: ** getcwd failure msg **");

	if (!info->argv[1])
	{
		chdir_res = ch_to_home_dir(info);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		chdir_res = ch_to_prev_dir(info, s);
	}
	else
	{
		chdir_res = chdir(info->argv[1]);
	}

	if (chdir_res == -1)
	{
		handle_dir_ch_err(info);
	}
	else
	{
		update_work_dir_env(info, buffer);
	}
	return (0);
}

/**
 * exit_shell - terminates shell processes
 * @info: struct containing potential arguments
 * Return: 0
 */
int exit_shell(info_t *info)
{
	int exit_code;

	if (info->argv[1])
	{
		exit_code = _err_atoi(info->argv[1]);
		if (exit_code == -1)
		{
			info->status = 2;
			print_error(info, "Unrecognized Number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _err_atoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * show_help - displays help information
 * @info: structure containing potential arguments
 * Return: Always 0
 */
int show_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("The help function was invoked. Function is not yet operational.\n");
	if (0)
		_puts(*arg_array);
	return (0);
}

/**
 * show_hist - displays command history with line numbers
 * @info: struct containing potential arguments
 * Return: Always 0
 */
int show_hist(info_t *info)
{
	print_list(info->hist);
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
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = rm_node(info->alias,
			get_node_ind(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;

	return (ret);
}
