#include "main.h"

/**
 * verify_env - Checks if the typed variable is an environment variable.
 * @hd: Head of the linked list.
 * @inp: Input string.
 * @shell_data: Data structure.
 *
 * Return: No return.
 */
void verify_env(r_var **hd, char *inp, shll_comm *shell_data)
{
	int line, charc, i, left_value;
	char **_env;

	_env = shell_data->_env;
	for (line = 0; _env[line]; line++)
	{
		for (i = 1, charc = 0; _env[line][charc]; charc++)
		{
			if (_env[line][charc] == '=')
			{
				left_value = _strlen(_env[line] + charc + 1);
				add_var_nd(hd, i, _env[line] + charc + 1, left_value);
				return;
			}

			if (inp[i] == _env[line][charc])
				i++;
			else
				break;
		}
	}

	for (i = 0; inp[i]; i++)
	{
		if (inp[i] == ' ' || inp[i] == '\t' || inp[i] == ';' || inp[i] == '\n')
			break;
	}

	add_var_nd(hd, i, NULL, 0);
}

/**
 * rpl_inp - Replaces variables in the input string.
 * @hd: Head of the linked list.
 * @inp: Input string.
 * @new_inp: New input string (replaced).
 * @numlen: New length.
 *
 * Return: Replaced string.
 */
char *rpl_inp(r_var **hd, char *inp, char *new_inp, int numlen)
{
	r_var *index;
	int i, l, m;

	index = *hd;
	for (l = i = 0; i < numlen; i++)
	{
		if (inp[l] == '$')
		{
			if (!(index->len_var) && !(index->len_val))
			{
				new_inp[i] = inp[l];
				l++;
			}
			else if (index->len_var && !(index->len_val))
			{
				for (m = 0; m < index->len_var; m++)
					l++;
				i--;
			}
			else
			{
				for (m = 0; m < index->len_val; m++)
				{
					new_inp[i] = index->val[m];
					i++;
				}
				l += (index->len_var);
				i--;
			}
			index = index->next;
		}
		else
		{
			new_inp[i] = inp[l];
			l++;
		}
	}

	return (new_inp);
}

/**
 * verify_vars - Check if the typed variable is $$ or $?
 * @header: Head of the linked list.
 * @inp: Input string.
 * @str: Last status of the shell.
 * @datashell: Data structure.
 *
 * Return: Number of characters processed.
 */
int verify_vars(r_var **header, char *inp, char *str, shll_comm *datashell)
{
	int i, leftst, leftpd;

	leftst = _strlen(str);
	leftpd = _strlen(datashell->pid);

	for (i = 0; inp[i]; i++)
	{
		if (inp[i] == '$')
		{
			if (inp[i + 1] == '?')
				add_var_nd(header, 2, str, leftst), i++;
			else if (inp[i + 1] == '$')
				add_var_nd(header, 2, datashell->pid, leftpd), i++;
			else if (inp[i + 1] == '\n')
				add_var_nd(header, 0, NULL, 0);
			else if (inp[i + 1] == '\0')
				add_var_nd(header, 0, NULL, 0);
			else if (inp[i + 1] == ' ')
				add_var_nd(header, 0, NULL, 0);
			else if (inp[i + 1] == '\t')
				add_var_nd(header, 0, NULL, 0);
			else if (inp[i + 1] == ';')
				add_var_nd(header, 0, NULL, 0);
			else
				verify_env(header, inp + i, datashell);
		}
	}

	return (i);
}

/**
 * compare_envname - Compares the name of an environment
 *                   variable with a given name.
 * @name_env: Name of the environment variable.
 * @name_ptr: Name to compare against.
 *
 * Return: 0 if the names are not equal. A value
 *         greater than 0 if they are equal.
 */
int compare_envname(const char *name_env, const char *name_ptr)
{
	int index;

	for (index = 0; name_env[index] != '='; index++)
	{
		if (name_env[index] != name_ptr[index])
		{
			return (0); /* Names do not match, return 0. */
		}
	}

	return (index + 1); /* Names match, return the position after '='. */
}
