#include "main.h"

/**
 * splt_ln - Tokenizes the input string.
 * @inp: Input string.
 *
 * Return: String splitted.
 */
char **splt_ln(char *inp)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(inp, TOK_DELIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += TOK_BUFSIZE;
			tokens = _reallocdp(tokens, i, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
		tokens[i] = token;
	}

	return (tokens);
}

/**
 * split_cmds - Splits command lines according to the separators ;, |, and &,
 *	      and executes them.
 * @datashell: Data structure.
 * @inp: Input string.
 *
 * Return: 0 to exit, 1 to continue.
 */
int split_cmds(shll_comm *datashell, char *inp)
{

	sep_list *hd_s, *ls_s;
	line_list *head_l, *list_l;
	int looping;

	hd_s = NULL;
	head_l = NULL;

	add_nd(&hd_s, &head_l, inp);

	ls_s = hd_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		datashell->input = list_l->line;
		datashell->args = splt_ln(datashell->input);
		looping = execute_line(datashell);
		free(datashell->args);

		if (looping == 0)
			break;

		move_nxt(&ls_s, &list_l, datashell);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_sp_ls(&hd_s);
	free_line_ls(&head_l);

	if (looping == 0)
		return (0);
	return (1);
}

/**
 * without_cmt - Deletes comments from the input.
 *
 * @input: Input string.
 * Return: Input without comments.
 */
char *without_cmt(char *input)
{
	int i, up_to;

	up_to = 0;
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '#')
		{
			if (i == 0)
			{
				free(input);
				return (NULL);
			}

			if (input[i - 1] == ' ' || input[i - 1] == '\t' || input[i - 1] == ';')
				up_to = i;
		}
	}

	if (up_to != 0)
	{
		input = _realloc(input, i, up_to + 1);
		input[up_to] = '\0';
	}

	return (input);
}

/**
 * looping_shll - Main loop of the shell
 * @data_shell: Data relevant to the shell (av, input, args)
 *
 * Return: No return.
 */
void looping_shll(shll_comm *data_shell)
{
	int looping, int_eof;
	char *inp;

	looping = 1;
	while (looping == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		inp = read_line(&int_eof);
		if (int_eof != -1)
		{
			inp = without_cmt(inp);
			if (inp == NULL)
				continue;

			if (ch_syn_err(data_shell, inp) == 1)
			{
				data_shell->stat = 2;
				free(inp);
				continue;
			}
			inp = replace_str(inp, data_shell);
			looping = split_cmds(data_shell, inp);
			data_shell->counter += 1;
			free(inp);
		}
		else
		{
			looping = 0;
			free(inp);
		}
	}
}

/**
 * add_var_nd - Adds a variable at the end of a r_var list.
 * @hd: Head of the linked list.
 * @lenvar: Length of the variable.
 * @value: Value of the variable.
 * @lenval: Length of the value.
 *
 * Return: Address of the head.
 */
r_var *add_var_nd(r_var **hd, int lenvar, char *value, int lenval)
{
	r_var *newnd, *tmp;

	newnd = malloc(sizeof(r_var));
	if (newnd == NULL)
		return (NULL);

	newnd->len_var = lenvar;
	newnd->val = value;
	newnd->len_val = lenval;

	newnd->next = NULL;
	tmp = *hd;

	if (tmp == NULL)
	{
		*hd = newnd;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = newnd;
	}

	return (*hd);
}
