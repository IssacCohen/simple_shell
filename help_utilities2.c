#include "main.h"

/**
 * disp_help_general - Entry point for help information for the help builtin
 *
 * Return: Void
 */
void disp_help_general(void)
{
	/* Display introductory information about the shell and available commands */
	char *hlp = "^-^ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "These commands are defined internally.Type 'help' to see the list";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "Type 'help name' to find out more about the function 'name'.\n\n ";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "unsetenv [variable]\n";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
}
/**
 * disp_help_exit - Help information fot the builint exit
 *
 * Return: Void
 */
void disp_help_exit(void)
{
	/* Display information about the 'exit' command */
	char *hlp = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "Exits the shell with a status of N. If N is ommited, the exit";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "statusis that of the last command executed\n";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
}

/**
 * display_unsetenv - Help information for the builtin unsetenv
 *
 * Return: Void
 */
void display_unsetenv(void)
{
	/* Display information about the 'unsetenv' command */
	char *hlp = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "Remove an entry completely from the environment\n";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
}

/**
 * get_sigint - Handle the crtl + c call in prompt
 * @sig: Signal handler
 */
void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}

/**
 * get_ln - assigns the line var for get_line
 * @lnptr: Pointer to the line variable
 * @num: Pointer to the size of line variable
 * @buf: String that is being assigned to line
 * @size_b: Size of the buffer
 *
 * Return: void
 */
void get_ln(char **lnptr, size_t *num, char *buf, size_t size_b)
{
	/* Check if the line pointer is initially NULL */
	if (*lnptr == NULL)
	{
		if (size_b > BUFSIZE)
			*num = size_b;

		else
			*num = BUFSIZE;
		*lnptr = buf;
	}
	/* Check if the existing line size is less than the buffer size */
	else if (*num < size_b)
	{
		if (size_b > BUFSIZE)
			*num = size_b;
		else
			*num = BUFSIZE;
		*lnptr = buf;
	}
	/* If neither condition is met, copy the buffer contents and free it */
	else
	{
		_strcpy(*lnptr, buf);
		free(buf);
	}
}
