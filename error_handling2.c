#include "main.h"
/**
 * error_404 - generates a generic error message for "command not found".
 * @data_sh: data relevant to the shell (counter, arguments).
 *
 * Return: The error message.
 */
char *error_404(shll_comm *data_sh)
{
	char *err, *vstr;
	int length;

	vstr = conv_itoa(data_sh->counter);
	length = _strlen(data_sh->argv[0]) + _strlen(vstr);
	length += _strlen(data_sh->args[0]) + 16;
	err = malloc(sizeof(char) * (length + 1));
	if (err == 0)
	{
		free(err);
		free(vstr);
		return (NULL);
	}
	_strcpy(err, data_sh->argv[0]);
	_strcat(err, ": ");
	_strcat(err, vstr);
	_strcat(err, ": ");
	_strcat(err, data_sh->args[0]);
	_strcat(err, ": not found\n");
	_strcat(err, "\0");
	free(vstr);

	return (err);
}

/**
 * err_shell_exit - generates a generic error message for
 *                  "exit" command in get_exit.
 * @data_sh: data relevant to the shell (counter, arguments).
 *
 * Return: The error message.
 */
char *err_shell_exit(shll_comm *data_sh)
{
	char *err, *vstr;
	int length;

	vstr = conv_itoa(data_sh->counter);
	length = _strlen(data_sh->argv[0]) + _strlen(vstr);
	length += _strlen(data_sh->args[0]) + _strlen(data_sh->args[1]) + 23;
	err = malloc(sizeof(char) * (length + 1));
	if (err == 0)
	{
		free(vstr);
		return (NULL);
	}
	_strcpy(err, data_sh->argv[0]);
	_strcat(err, ": ");
	_strcat(err, vstr);
	_strcat(err, ": ");
	_strcat(err, data_sh->args[0]);
	_strcat(err, ": Illegal number: ");
	_strcat(err, data_sh->args[1]);
	_strcat(err, "\n\0");
	free(vstr);

	return (err);
}

/**
 * err_gcd - generates an error message for the 'cd' command in get_cd.
 * @data_sh: data relevant to the shell (directory).
 *
 * Return: The error message.
 */
char *err_gcd(shll_comm *data_sh)
{
	char *err, *vstr, *errmsg;
	int len, lenid;

	vstr = conv_itoa(data_sh->counter);
	if (data_sh->args[1][0] == '-')
	{
		errmsg = ": Illegal option ";
		lenid = 2;
	}
	else
	{
		errmsg = ": can't cd to ";
		lenid = _strlen(data_sh->args[1]);
	}

	len = _strlen(data_sh->argv[0]) + _strlen(data_sh->args[0]);
	len += _strlen(vstr) + _strlen(errmsg) + lenid + 5;
	err = malloc(sizeof(char) * (len + 1));

	if (err == 0)
	{
		free(vstr);
		return (NULL);
	}

	err = conc_err_msg(data_sh, errmsg, err, vstr);

	free(vstr);

	return (err);
}
