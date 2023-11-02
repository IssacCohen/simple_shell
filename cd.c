#include "main.h"

/**
 * changedir_shell - Changes the current directory.
 * @data_sh: Pointer to the data
 *
 * Return: 1 on success.
 */
int changedir_shell(shll_comm *data_sh)
{
	int inhome, inhome2, isdashboard;
	char *directory = data_sh->args[1];

	if (directory != NULL)
	{
		inhome = _strcmp("$HOME", directory);
		inhome2 = _strcmp("~", directory);
		isdashboard = _strcmp("--", directory);
	}
/* Check if the directory is NULL or matches special cases */
	if (directory == NULL || !inhome || !inhome2 || !isdashboard)
	{
		changedir_to_home(data_sh);
		return (1);
	}
/* Check if the directory is "-" */

	if (_strcmp("-", directory) == 0)
	{
		changedir_prev(data_sh);
		return (1);
	}
/* Check if the directory is "." or ".." */

	if (_strcmp(".", directory) == 0 || _strcmp("..", directory) == 0)
	{
		chandir_dor(data_sh);
		return (1);
	}

	cd_to_dist(data_sh);

	return (1);
}

/**
 * chandir_dor - Changes to the parent directory.
 * @data_sh: Pointer to the data structure containing the
 *           environment variables.
 *
 * Return: No return value.
 */
void chandir_dor(shll_comm *data_sh)
{
	char pwd[PATH_MAX];
	char *directory, *cp_printwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_printwd = _strdup(pwd);
	set_env("OLDPWD", cp_printwd, data_sh);
	directory = data_sh->args[1];
	if (_strcmp(".", directory) == 0)
	{
		set_env("PWD", cp_printwd, data_sh);
		free(cp_printwd);
		return;
	}
	if (_strcmp("/", cp_printwd) == 0)
	{
		free(cp_printwd);
		return;
	}
	cp_strtok_pwd = cp_printwd;
	rev_string(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			rev_string(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_env("PWD", cp_strtok_pwd, data_sh);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", data_sh);
	}
	data_sh->stat = 0;
	free(cp_printwd);
}

/**
 * cd_to_dist - Changes to a directory specified by the user.
 * @data_sh: Pointer to the data structure containing
 *           the directories.
 *
 * Return: No return value.
 */
void cd_to_dist(shll_comm *data_sh)
{
	char printwd[PATH_MAX];
	char *directory, *cp_pwd, *cp_dir;
/* Get the current working directory */
	getcwd(printwd, sizeof(printwd));

	directory = data_sh->args[1];
	if (chdir(directory) == -1)
	{
		/* Handle directory change failure */
		get_err(data_sh, 2);
		return;
	}

	cp_pwd = _strdup(printwd);
	set_env("OLDPWD", cp_pwd, data_sh);

	cp_dir = _strdup(directory);
	set_env("PWD", cp_dir, data_sh);
/* Free memory allocated for copies */
	free(cp_pwd);
	free(cp_dir);
/* Reset the shell status to 0 */
	data_sh->stat = 0;
/* Change to the specified directory */
	chdir(directory);
}

/**
 * changedir_prev - Changes to the previous directory.
 * @data_sh: Data relevant to the environment and
 *           directories.
 *
 * Return: No return value.
 */
void changedir_prev(shll_comm *data_sh)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	p_oldpwd = get_environ("OLDPWD", data_sh->_env);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);

	set_env("OLDPWD", cp_pwd, data_sh);

	if (chdir(cp_oldpwd) == -1)
		set_env("PWD", cp_pwd, data_sh);
	else
		set_env("PWD", cp_oldpwd, data_sh);

	p_pwd = get_environ("PWD", data_sh->_env);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	data_sh->stat = 0;

	chdir(p_pwd);
}

/**
 * changedir_to_home - Changes to the home directory.
 * @data_sh: Data relevant to the environment.
 *
 * Return: No return value.
 */
void changedir_to_home(shll_comm *data_sh)
{
	char *print_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	print_pwd = _strdup(pwd);

	home = get_environ("HOME", data_sh->_env);

	if (home == NULL)
	{
		set_env("OLDPWD", print_pwd, data_sh);
		free(print_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_err(data_sh, 2);
		free(print_pwd);
		return;
	}

	set_env("OLDPWD", print_pwd, data_sh);
	set_env("PWD", home, data_sh);
	free(print_pwd);
	data_sh->stat = 0;
}
