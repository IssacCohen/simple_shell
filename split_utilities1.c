#include "main.h"

/**
 * move_nxt - Moves to the next command line stored.
 * @lis_s: Separator list.
 * @lis_l: Command line list.
 * @data_shell: Data structure.
 *
 * Return: No return value.
 */
void move_nxt(sep_list **lis_s, line_list **lis_l, shll_comm *data_shell)
{
	int loop_sep;
	sep_list *ls_s;
	line_list *ls_l;

	loop_sep = 1;
	ls_s = *lis_s;
	ls_l = *lis_l;

	while (ls_s != NULL && loop_sep)
	{
		if (data_shell->stat == 0)
		{
			if (ls_s->sep == '&' || ls_s->sep == ';')
				loop_sep = 0;
			if (ls_s->sep == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->sep == '|' || ls_s->sep == ';')
				loop_sep = 0;
			if (ls_s->sep == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}
	*lis_s = ls_s;
	*lis_l = ls_l;
}

/**
 * swp_character - Swaps '|' and '&' for non-printed characters
 *                 in a string.
 * @inp: Input string.
 * @boolean: Type of swap. If boolean is 0, swaps '|' and '&'
 *           for non-printed characters.
 *
 * Return: Swapped string.
 */
char *swp_character(char *inp, int boolean)
{
	int i;

	if (boolean == 0)
	{
		for (i = 0; inp[i]; i++)
		{
			if (inp[i] == '|')
			{
				if (inp[i + 1] != '|')
					inp[i] = 16;
				else
					i++;
			}

			if (inp[i] == '&')
			{
				if (inp[i + 1] != '&')
					inp[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; inp[i]; i++)
		{
			inp[i] = (inp[i] == 16 ? '|' : inp[i]);
			inp[i] = (inp[i] == 12 ? '&' : inp[i]);
		}
	}
	return (inp);
}

/**
 * add_nd - Adds separators and command lines to the lists.
 * @hd_s: Head of the separator list.
 * @hd_l: Head of the command lines list.
 * @inp: Input string.
 *
 * Return: No return value.
 */
void add_nd(sep_list **hd_s, line_list **hd_l, char *inp)
{
	int i;
	char *command_line;

	inp = swp_character(inp, 0);

	for (i = 0; inp[i]; i++)
	{
		if (inp[i] == ';')
			add_node_en(hd_s, inp[i]);

		if (inp[i] == '|' || inp[i] == '&')
		{
			add_node_en(hd_s, inp[i]);
			i++;
		}
	}

	command_line = _strtok(inp, ";|&");
	do {
		command_line = swp_character(command_line, 1);
		add_ln_nd_end(hd_l, command_line);
		command_line = _strtok(NULL, ";|&");
	} while (command_line != NULL);
}
/**
 * read_line - Reads the input string.
 * @int_eof: Return value of the getline function.
 *
 * Return: Input string.
 */
char *read_line(int *int_eof)
{
	char *inp = NULL;
	size_t buffersize = 0;

	*int_eof = getline(&inp, &buffersize, stdin);

	return (inp);
}
/**
 * free_value_ls - Frees a r_var list.
 * @hd: Head of the linked list.
 * Return: No return.
 */
void free_value_ls(r_var **hd)
{
	r_var *tmp;
	r_var *current;

	if (hd != NULL)
	{
		current = *hd;
		while ((tmp = current) != NULL)
		{
			current = current->next;
			free(tmp);
		}
		*hd = NULL;
	}
}
