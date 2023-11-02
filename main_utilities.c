#include "main.h"

/**
 * get_err - Calls the error message according to the
 *	   builtin, syntax, or permission
 * @datashell: Data structure that contains arguments
 * @error_val: Error value
 *
 * Return: Error value
 */
int get_err(shll_comm *datashell, int error_val)
{
	char *error;
/* Determine the error type based on the error code (error_val). */
	switch (error_val)
	{
	case -1:
		error = err_environ(datashell);
		break;
	case 126:
		error = err_path126(datashell);
		break;
	case 127:
		error = error_404(datashell);
		break;
	case 2:
		if (_strcmp("exit", datashell->args[0]) == 0)
			error = err_shell_exit(datashell);
		else if (_strcmp("cd", datashell->args[0]) == 0)
			error = err_gcd(datashell);
		break;
	}
	if (error)
	{
		/* Output error message and release memory. */
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}
	datashell->stat = error_val;
	return (error_val);
}

/**
 * empty_data - frees data structure.
 * @data_shell: data structure.
 *
 * Return: no return.
 */
void empty_data(shll_comm *data_shell)
{
	unsigned int index;
/* Free the memory allocated for the elements of the _env array. */
	for (index = 0; data_shell->_env[index]; index++)
		free(data_shell->_env[index]);

	free(data_shell->_env);
	free(data_shell->pid);
}

/**
 * set_datashell - Initialize data structure
 * @data_shell: data structure
 * @argv: argument vector
 *
 * Return: no return
 */
void set_datashell(shll_comm *data_shell, char **argv)
{
	unsigned int i;

	data_shell->argv = argv;
	data_shell->input = NULL;
	data_shell->args = NULL;
	data_shell->stat = 0;
	data_shell->counter = 1;
	for (i = 0; environ[i]; i++)
		;
	data_shell->_env = malloc(sizeof(char *) * (i + 1));
	for (i = 0; environ[i]; i++)
	{
		data_shell->_env[i] = _strdup(environ[i]);
	}
	data_shell->_env[i] = NULL;
	data_shell->pid = conv_itoa(getpid());
}

/**
 * get_hlp - Function that retrieves help messages
 *	   according to built-in command
 * @data_shll: Data structure (args and input)
 *
 * Return: 1
 */
int get_hlp(shll_comm *data_shll)
{

	if (data_shll->args[1] == 0)
		disp_help_general();
	else if (_strcmp(data_shll->args[1], "setenv") == 0)
		disp_help_setenv();
	else if (_strcmp(data_shll->args[1], "env") == 0)
		disp_help_env();
	else if (_strcmp(data_shll->args[1], "unsetenv") == 0)
		display_unsetenv();
	else if (_strcmp(data_shll->args[1], "help") == 0)
		disp_help();
	else if (_strcmp(data_shll->args[1], "exit") == 0)
		disp_help_exit();
	else if (_strcmp(data_shll->args[1], "cd") == 0)
		disp_help_cd();
	else if (_strcmp(data_shll->args[1], "alias") == 0)
		disp_help_alias();
	else
		write(STDERR_FILENO, data_shll->args[0],
		      _strlen(data_shll->args[0]));
	data_shll->stat = 0;
	return (1);
}

/**
 * get_bltn - Retrieves the function pointer of the builtin command
 * @command: Command line
 *
 * Return: Function pointer of the builtin command
 */
int (*get_bltn(char *command))(shll_comm *)
{
	builtin_t bltn[] = {
	    {"env", display_env},
	    {"exit", exit_sh},
	    {"setenv", _setenv},
	    {"unsetenv", _unsetenv},
	    {"cd", changedir_shell},
	    {"help", get_hlp},
	    {NULL, NULL}};
	int index;

	for (index = 0; bltn[index].commname; index++)
	{
		if (_strcmp(bltn[index].commname, command) == 0)
			break;
	}
	return (bltn[index].f);
}
