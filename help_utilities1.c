#include "main.h"

/**
 * disp_help_cd - Help information for the builtin alias.
 *
 * Return: no return
 */
void disp_help_cd(void)
{
	char *hlp = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";
/* Print the command description */
	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
}

/**
 * disp_help_alias - Help information for the builtin alias.
 *
 * Return: no return
 */
void disp_help_alias(void)
{
	/* Display the usage information for the 'alias' command */
	char *hlp = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
}

/**
 * disp_help - Help information for the builtin help.
 *
 * Return: no return
 */
void disp_help(void)
{
	char *hlp = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
}

/**
 * disp_help_env - Help information for the builtin env
 *
 * Return: no return
 */
void disp_help_env(void)
{
	/* Display the usage information for the 'env' command */
	char *hlp = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "Print the enviroment of the shell.\n";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
}

/**
 * disp_help_setenv - Help information for the builtin setenv
 *
 * Return: no return
 */
void disp_help_setenv(void)
{
	/* Display the usage information for the 'setenv' command */
	char *help = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "int replace)\n\t";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, help, _strlen(help));
}
