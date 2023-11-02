#include "main.h"

/**
 * first_character - finds the index of the first non-whitespace character.
 * @inp: intptr_t string.
 * @index: pointer to the index variable.
 *
 * Return: 1 if there is an error, 0 otherwise.
 */
int first_character(char *inp, int *index)
{

	for (*index = 0; inp[*index]; *index += 1)
	{
		if (inp[*index] == ' ' || inp[*index] == '\t')
			continue;

		if (inp[*index] == ';' || inp[*index] == '|' || inp[*index] == '&')
			return (-1);
/* Found the first non-whitespace character */
		break;
	}
/* Success: No special characters found */
	return (0);
}

/**
 * disp_syn_err - displays a syntax error message.
 * @data_sh: data structure.
 * @inp: intptr_t string.
 * @index: index of the error.
 * @boolean: flag to control the error message.
 *
 * Return: No return value.
 */
void disp_syn_err(shll_comm *data_sh, char *inp, int index, int boolean)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	if (inp[index] == ';')
	{
		if (boolean == 0)
			msg = (inp[index + 1] == ';' ? ";;" : ";");
		else
			msg = (inp[index - 1] == ';' ? ";;" : ";");
	}

	if (inp[index] == '|')
		msg = (inp[index + 1] == '|' ? "||" : "|");

	if (inp[index] == '&')
		msg = (inp[index + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = conv_itoa(data_sh->counter);
	length = _strlen(data_sh->argv[0]) + _strlen(counter);
	length += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_strcpy(error, data_sh->argv[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, msg2);
	_strcat(error, msg);
	_strcat(error, msg3);
	_strcat(error, "\0");
/* Write the error message to stderr */
	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}

/**
 * ch_syn_err - intermediate function to find and print a syntax error.
 * @data_sh: data structure.
 * @inptrt: intptr_t string.
 *
 * Return: 1 if there is an error, 0 otherwise.
 */
int ch_syn_err(shll_comm *data_sh, char *inptrt)
{
	int start = 0, fcharac = 0, index = 0;

	fcharac = first_character(inptrt, &start);
	if (fcharac == -1)
	{
		disp_syn_err(data_sh, inptrt, start, 0);
		return (1);
	}

	index = sep_oper_error(inptrt + start, 0, *(inptrt + start));
	if (index != 0)
	{
		disp_syn_err(data_sh, inptrt, start + index, 1);
		return (1);
	}

	return (0);
}

/**
 * dupl_chars - counts the repetitions of a character in a string.
 * @inp: intptr_t string.
 * @index: index.
 *
 * Return: The number of repetitions.
 */
int dupl_chars(char *inp, int index)
{
	if (*(inp - 1) == *inp)
		return (dupl_chars(inp - 1, index + 1));

	return (index);
}

/**
 * sep_oper_error - finds syntax errors in the intptr_t string.
 * @inp: intptr_t string.
 * @index: index.
 * @lastchar: last character read.
 *
 * Return: The index of the error. Returns 0 when there are no errors.
 */
int sep_oper_error(char *inp, int index, char lastchar)
{
	int counter = 0;

	if (*inp == '\0')
		return (0);

	if (*inp == ' ' || *inp == '\t')
		return (sep_oper_error(inp + 1, index + 1, lastchar));

	if (*inp == ';')
		if (lastchar == '|' || lastchar == '&' || lastchar == ';')
			return (index);

	if (*inp == '|')
	{
		if (lastchar == ';' || lastchar == '&')
			return (index);

		if (lastchar == '|')
		{
			counter = dupl_chars(inp, 0);
			if (counter == 0 || counter > 1)
				return (index);
		}
	}

	if (*inp == '&')
	{
		if (lastchar == ';' || lastchar == '|')
			return (index);

		if (lastchar == '&')
		{
			counter = dupl_chars(inp, 0);
			if (counter == 0 || counter > 1)
				return (index);
		}
	}

	return (sep_oper_error(inp + 1, index + 1, *inp));
}
