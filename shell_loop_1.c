#include "shell.h"

/**
 * shell_loop - Reads and executes commands and param from the command line
 * @argv: argument vector
 * Return: loop status
 */
int shell_loop(char **argv)
{
	if (isatty(STDIN_FILENO))
		return (result(argv));

	else
		return (no_result(argv));
}

/**
 * shell_getline - Reads a line from standard input
 * Return: commands and param from standard input
 */
char *shell_getline(void)
{
	unsigned int len = READ_BUFFER_SIZE, pin = 0;
	int i;
	char *line_buffer = malloc(sizeof(char) * len);

	if (line_buffer == NULL)
	{
		perror("Malloc failed: cannot allocate memory");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		i = shell_getchar();
		if (i == EOF)
		{
			free(line_buffer);
			exit(EXIT_SUCCESS);
		}

		else if (ci == '\n')
		{
			line_buffer[pin] = '\0';
			return (line_buffer);
		}
		else
			line_buffer[pin] = ch;
		pin += 1;
	}
	if (pin >= len)
	{
		len += READ_BUFFER_SIZE;
		line_buffer = shell_realloc(line_buffer, len, sizeof(char) * len);
		if (line_buffer == NULL)
		{
			perror("Failed to allocate memory");
			exit(EXIT_FAILURE);
		}
	}
}

/**
 * shell_execute - Executes the command to be parsed
 * @av1: Null terminated array without entry ':'
 * @av2: Null terminated array to handle entry ':'
 * @argv: Argument vector
 * @cli_arg: string input from getline
 * @line_count: The count of processed lines
 * Return: Always 1
 */
int shell_execute(char **av1, char **av2, char **argv, char *cli_arg,
		int line_count)
{
	int i = 0, builtin_count, res;
	char **num;
	char *builtin[] = {
		"cd",
		"env",
		"setenv",
		"unsetenv",
	};
	int (*builtin_opr[])(char **, char **, int) = {
		&shell_cd,
		&env_builtin,
		&set_env_builtin,
		&unset_env_builtin,
	};

	if (cli_arg == NULL)
		return (1);
	builtin_count = sizeof(builtin) / sizeof(char *);
	while (i < builtin_count)
	{
		if (strcompare(av1[0], builtin[i]) == 0)
		{
			res = (*builtin_opr[i])(argv, av1, line_count);
			return (res);
		}
		i++;
	}
	if (find_char(cli_arg, ';') != NULL)
	{
		while (*av2)
		{
			num = parse_line1(*av2);
			fork_cmd(num, argv, line_count);
			free(num);
			av2++;
		}
	}
	else
		fork_cmd(av1, argv, line_count);
	return (1);
}

/**
 * parse_line1 - seperates the command string into commands and param
 * @cli_arg: command sring from stdin
 * Return: A terminated array of token strings
 */
char **parse_line1(char *cli_arg)
{
	unsigned int len = TOKEN_BUFFER, pin_size = 0;
	char **num_buf, numc, nums;

	if (cli_arg == NULL)
	return (NULL);

	num_buf = malloc(sizeof(char *) * len);

	if (num_buf == NULL)
	{
		perror("Malloc failed: cannot allocate memory");
		exit(EXIT_FAILURE);
	}

	nums = stok_delim(cli_arg, DELIMITERS);

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
				perror("Failed: Could not re-allocate memory");
				exit(EXIT_FAILURE);
			}
		}
		nums = stok_delim(NULL, DELIMITERS);
	}
	num_buf[pin] = NULL;
	return (num_buf);
}

/**
 * fork_cmd - Forks a child process and waits for it to execute a command
 * @av: Null termianted list of commands and param
 * @argv: Argument vector
 * @line_count: The count of lines processed
 * Return: 1 (Succes), 0 (Otherwise)
 */
int fork_cmd(char **av, char **argv, int line_count)
{
	int res;
	char *all_path = find_command(av);
	pid_t child_process;

	if (all_path == NULL)
	{
		eput(argv[0], av, "not found", line_count);
		return (1);
	}
	child_process = fork();

	if (child_process == -1)
		eputchar("Failed");
	if (child_process == 0)
	{
		if (execve(all_path, av, environ) == -1)
		{
			if (errno == EACCES)
				eputchar("Permission denied for execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		do {
			waitpid(child_process, &ret_status, WUNTRACED);
		} while (!WIFEXITED(res) && !WIFSIGNALED(res));
	}
	free(all_path);
	return (1);
}
