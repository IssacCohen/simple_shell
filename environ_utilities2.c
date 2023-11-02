#include "main.h"

/**
 * replace_str - Calls functions to replace string into vars.
 * @inp: Input string.
 * @data_shell: Data structure.
 *
 * Return: Replaced string.
 */
char *replace_str(char *inp, shll_comm *data_shell)
{
	int olen, nlen;
	r_var *hd, *index;
	char *stat, *new_inp;

	stat = conv_itoa(data_shell->stat);
	hd = NULL;

	olen = verify_vars(&hd, inp, stat, data_shell);

	if (hd == NULL)
	{
		free(stat);
		return (inp);
	}

	index = hd;
	nlen = 0;

	while (index != NULL)
	{
		nlen += (index->len_val - index->len_var);
		index = index->next;
	}

	nlen += olen;

	new_inp = malloc(sizeof(char) * (nlen + 1));
	new_inp[nlen] = '\0';

	new_inp = rpl_inp(&hd, inp, new_inp, nlen);

	free(inp);
	free(stat);
	free_value_ls(&hd);

	return (new_inp);
}

/**
 * _unsetenv - Deletes an environment variable with the specified name.
 * @datash: Data structure containing the environment variable name.
 *
 * Return: 1 on success.
 */
int _unsetenv(shll_comm *datash)
{
	int i, j, k;
	char **real_env;
	char *varenv, *nmenv;

	if (datash->args[1] == NULL)
	{
		get_err(datash, -1);
		return (1);
	}
	k = -1;
	for (i = 0; datash->_env[i]; i++)
	{
		varenv = _strdup(datash->_env[i]);
		nmenv = _strtok(varenv, "=");
		if (_strcmp(nmenv, datash->args[1]) == 0)
		{
			k = i;
		}
		free(varenv);
	}
	if (k == -1)
	{
		get_err(datash, -1);
		return (1);
	}
	real_env = malloc(sizeof(char *) * (i));
	for (i = j = 0; datash->_env[i]; i++)
	{
		if (i != k)
		{
			real_env[j] = datash->_env[i];
			j++;
		}
	}
	real_env[j] = NULL;
	free(datash->_env[k]);
	free(datash->_env);
	datash->_env = real_env;
	return (1);
}

/**
 * set_env - Sets an environment variable.
 * @environ_name: Name of the environment variable.
 * @val: Value of the environment variable.
 * @data_sh: Data structure containing the environment variables.
 *
 * Return: No return.
 */
void set_env(char *environ_name, char *val, shll_comm *data_sh)
{
	int i;
	char *varenv, *nmenv;

	for (i = 0; data_sh->_env[i]; i++)
	{
		varenv = _strdup(data_sh->_env[i]);
		nmenv = _strtok(varenv, "=");
		if (_strcmp(nmenv, environ_name) == 0)
		{
			free(data_sh->_env[i]);
			data_sh->_env[i] = cp_info(nmenv, val);
			free(varenv);
			return;
		}
		free(varenv);
	}

	data_sh->_env = _reallocdp(data_sh->_env, i, sizeof(char *) * (i + 2));
	data_sh->_env[i] = cp_info(environ_name, val);
	data_sh->_env[i + 1] = NULL;
}

/**
 * _setenv - compares env variables names
 *           with the name passed.
 * @data_sh: data relevant (env name and env value)
 *
 * Return: 1 on success.
 */
int _setenv(shll_comm *data_sh)
{

	if (data_sh->args[1] == NULL || data_sh->args[2] == NULL)
	{
		get_err(data_sh, -1);
		return (1);
	}

	set_env(data_sh->args[1], data_sh->args[2], data_sh);

	return (1);
}

/**
 * cp_info - Copies information to create a new environment variable or alias.
 * @alias_name: Name of the environment variable or alias.
 * @val: Value of the environment variable or alias.
 *
 * Return: New environment variable or alias.
 */
char *cp_info(char *alias_name, char *val)
{
	char *new;
	int len_name, len_value, len;

	len_name = _strlen(alias_name);
	len_value = _strlen(val);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, alias_name);
	_strcat(new, "=");
	_strcat(new, val);
	_strcat(new, "\0");

	return (new);
}
