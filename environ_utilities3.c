#include "main.h"

/**
 * get_environ - Get the value of an environment variable.
 * @envname: Name of the environment variable.
 * @_env: Array of environment variables.
 *
 * Return: A pointer to the value of the environment variable
 *         if it is found.
 *         NULL if the environment variable is not found.
 */
char *get_environ(const char *envname, char **_env)
{
	char *ptr_env;
	int i, mov;

	/* Initialize ptr_env value */
	ptr_env = NULL;
	mov = 0;
	/* Compare all environment variables */
	/* environ is declared in the header file */
	for (i = 0; _env[i]; i++)
	{
		/* If name and env are equal */
		mov = compare_envname(_env[i], envname);
		if (mov)
		{
			ptr_env = _env[i];
			break;
		}
	}

	return (ptr_env + mov);
}

/**
 * display_env - Print the environment variables.
 * @data_sh: Pointer to the data structure containing the
 *           environment variables.
 *
 * Return: 1 on success.
 */
int display_env(shll_comm *data_sh)
{
	int l, m;

	for (l = 0; data_sh->_env[l]; l++)
	{

		for (m = 0; data_sh->_env[l][m]; m++)
			;

		write(STDOUT_FILENO, data_sh->_env[l], m);
		write(STDOUT_FILENO, "\n", 1);
	}
	data_sh->stat = 0;

	return (1);
}

/**
 * _getline - Read input from stream
 * @lnptr: Pointer to the buffer that stores the input
 * @num: Pointer to the size of lnptr
 * @filestream: Stream to read from
 *
 * Return: The number of bytes
 */
ssize_t _getline(char **lnptr, size_t *num, FILE *filestream)
{
	int index;
	static ssize_t inp;
	ssize_t retval;
	char *buffer;
	char t = 'z';

	if (inp == 0)
		fflush(filestream);
	else
		return (-1);
	inp = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		index = read(STDIN_FILENO, &t, 1);
		if (index == -1 || (index == 0 && inp == 0))
		{
			free(buffer);
			return (-1);
		}
		if (index == 0 && inp != 0)
		{
			inp++;
			break;
		}
		if (inp >= BUFSIZE)
			buffer = _realloc(buffer, inp, inp + 1);
		buffer[inp] = t;
		inp++;
	}
	buffer[inp] = '\0';
	get_ln(lnptr, num, buffer, inp);
	retval = inp;
	if (index != 0)
		inp = 0;
	return (retval);
}
