#include "shell.h"

/**
 * create_env_str - creates the name value string
 * @var_name: the env variavle to be created
 * @val: value to assign
 * Return: New env var created / NULL
 */
char *create_env_str(char *var_name, char *val)
{
	size_t name_len = strlen(var_name);
	size_t val_len = strlen(val);

	char *new_var = (char *)malloc(name_len + 1 + val_len + 1);

	if (new_var == NULL)
	{
		eputchar("Failed: Memory allocation");
		return (NULL);
	}

	strcpy(new_var, var_name);
	strconcat(new_var, "=");
	strconcat(new_var, val);

	return (new_var);
}

/**
 * shell_unsetenv - removes an env variable
 * @var_name: the env variables to create
 * Return: 0 (Success), -1 (Failure)
 */
int shell_unsetenv(char *var_name)
{
	int i, a, flag;
	char ** env_ptr = environ;

	if (!var_name || !env_ptr)
		return (-1);

	flag = -1;

	for (a = 0; env_ptr[a] != NULL; a++;)
	{
		if (str_n_cmp(env_ptr[a], var_name, strlen(var_name)) == 0
				&& env_ptr[a][strlen(var_name)] == '=')
		{
			flag = a;
			break;
		}
	}
	if (flag == -1)
		return (0);
	for (i = flag; env_ptr[i] != NULL; i++)
		env_ptr[i] = env_ptr[i + 1];

	return (0);
}


