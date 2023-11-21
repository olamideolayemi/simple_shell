#include "shell.h"

/**
 * parse_line2 - Seperates the command string into commands and param
 * @cli_arg: Command string from stdin
 * Return: A Null terminated array of token strings
 */
char **parse_line2(char *cli_arg)
{
	unsigned int len = TOKEN_BUFFER, pin = 0;
	char **num_buf, numc, nums;

	if (get_char(cli_arg, ';') == NULL || cli_arg == NULL)
		return (NULL);

	num_buf = malloc(sizeof(char *) * len);

	if (num_buf == NULL)
	{
		eputchar("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}
	nums = stok_delim(cli_arg, ";");

	while (nums != NULL)
	{
		num_buf[pin] = nums;
		pin++;

		if (pin >= len)
		{
			len += TOKEN_BUFFER;
			numc = num_buf;
			num_buf = shell_realloc(num_buf, len, sizeof(char *) * len);

			if (!num_buf)
			{
				free(numc);
				eputchar("Failed: cannot re-allocate memory");
				exit(EXIT_FAILURE);
			}
		}
		nums = stok_delim(NULL, ";");
	}
	num_buf[pin] = NULL;
	return (num_buf);
}
/**
 * inter - starts the shell in interactive mode
 * @argv: Argument vector
 * Return: 0 (Success), -1 (Failure)
 */
int inter(char **argv)
{
	char **arg_parse1, **arg_parse2, *cli_arg1, *cli_arg2, *cli_arg3;
	int res, line_count = 1;

	do {
		_puts(" ** ->> ");
		fflush(stdout);

		cli_arg1 = shell_getline();
		cli_arg2 = strdup(cli_arg1);
		cli_arg3 = strdup(cli_arg1);

		arg_parse1 = parse_line1(cli_arg1);
		arg_parse2 = parse_line2(cli_arg2);

		if (strcomp(arg_parse[0], "exit") == 0)
			res = shell_exit(argv, arg_parse1, line_count);
		else
			res = shell_exec(arg_parse1, arg_parse2, argv,
					cli_arg3, line_count);

		free_loop(&cli_arg1, &cli_arg2, &cli_arg3, &arg_parse1, &arg_parse2);

		line_count++;
	} while (res == 1);


	return (res);
}

/**
 * non_inter - starts the shell in non-interactive mode
 * @argv: argument vector
 * Return: 0 (Success)
 */
int non_inter(char **argv)
{
	char **arg_parse1, **arg_parse2, *cli_arg1, *cli_arg2, *cli_arg3;
	int res, line_count = 1;

	cli_arg1 = shell_getline();
	cli_arg2 = strdup(cli_arg1);
	cli_arg3 = strdup(cli_arg1);

	arg_parse1 = parse_line1(cli_arg1);
	arg_parse2 = parse_line2(cli_arg2);

	if (strcomp(arg_parse[0], "exit") == 0)
	{
		res = shell_exit(argv, arg_parse1, line_count);
		free_loop(&cli_arg1, &cli_arg2, &cli_arg3, &arg_parse1, &arg_parse2);

		return (res);
	}
	else
	{
		shell_exec(arg_parse1, arg_parse2, argv, cli_arg3, line_count);
		free_loop(&cli_arg1, &cli_arg2, &cli_arg3, &arg_parse1, &arg_parse2);

		return (EXIT_SUCCESS);
	}
}
