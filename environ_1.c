#include "shell.h"

/**
 * shell_env - Retrives a copy of the environ array
 * Return: an array of strings
 */
char **shell_env(void)
{
	int i = 0, env_count = 0;
	char **env_cpy;

	while (environ[env_count] != NULL)
		env_count++;

	env_cpy = (char **)malloc(sizeof(char *) * (env_count + 1));

	if (env_cpy == NULL)
	{
		eputchar("Failed: Memory allocations failed");
		exit(EXIT_FAILURE);
	}

	while (environ[i] != NULL)
	{
		env_cpy[i] = strdup(environ[i]);
		if (env_cpy[i] == NULL)
		{
			eputchar("Failed: Memory allocation failed");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	env_cpy[i] = NULL;
	return (env_cpy);
}

/**
 * shell_setenv - craetes/updates values of an env var
 * @var_name: The env var to craete/update
 * @val: the value to assign to env var
 * @flag: 1 (update value to new value), 0 (do not flag)
 * Return: 0 (Success) / -1 (Otherwise)
 */
int shell_setenv(char *var_name, char *val, int flag)
{
	char *var;

	if (var_name == NULL || var_name[0] == '\0' ||
			find_char(var_name, '=') != NULL)
	{
		eputchar("Invalid var name");
		return (-1);
	}
	if (shell_getenv(var_name) != NULL && !flag)
		return (0);

	var = malloc(strlen(var_name) + strlen(val) + 2);
	if (var == NULL)
	{
		eputchar("Failed: Can not alooctae memory");
		return (-1);
	}
	strcpy(var, var_name);
	strconcat(var, "=");
	strconcat(var, val);

	if (putenv(var) != 0)
	{
		eputchar("Failed: Could not set variable");
		free(var);
		return (-1);
	}
	free(var);
	return (0);
}

/**
 * shell_getenv - gets the value of an environ var
 * @var_name: environ variable prefix
 * Return: environ variable value
 */
char *shell_getenv(char *var_name)
{
	int i = 0;

	if (!var_name || !environ)
		return (NULL);
	while (environ[i] != NULL)
	{
		if (str_n_cmp(environ[i], var_name, strlen(var_name)) == 0
				&& environ[i][strlen(var_name)] == '=')
			return (environ[i] + strlen(var_name) + 1);
		i++;
	}
	return (NULL);
}

/**
 * add_shell - adds/ replaces env variables
 * @var_name: Env variable to be added/replaced
 * @val: the env variables value
 * Return: 0 (SUceess), -1 (Otherwise)
 */
int add_shell(char *var_name, char *val)
{
	char *new_var, **new_env;
	int v, i, env_count = 0;

	if (!var_name || !value)
		return (-1);
	new_var = create_env(var_name, value);

	if (!new_var)
		return (-1);
	v = check_env(var_name);

	if (var_i != 0)
	{
		free(environ[v]);
		environ[v] = new_var;
	}
	else
	{
		while (environ[env_count] != NULL)
			env_count++;
		new_env = (char **)malloc((env_count + 2) * sizeof(char *));

		if (!new_env)
		{
			free(new_var);
			return (-1);
		}
		for (i = 0; i < env_count; i++)
			new_env[i] = environ[i];
		new_env[env_count] = new_var;
		new_env[env_count + 1] = NULL;

		free(environ);
		environ = new_env;
	}
	return (0);
}

/**
 * check_env - checks if env variable exist
 * @var_name: env varibale string
 * Return: 1 (env variable exists), 0 (Otherwise)
 */
int check)env(char *var_name)
{
	int i;

	if (var_name ++ NULL)
		return (0);

	for (i = 0; environ[i] != NULL; i++)
	{
		if (str_n_cmp(environ[i], var_name, strlen(var_name)) == 0
				&& environ[i][strlen(var_name)] == '=')
		return (i);
	}
	return (0);
}
