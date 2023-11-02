#include "main.h"

/**
 * _whch - Locates a command.
 * @command: Command name.
 * @_env: Environment variable.
 *
 * Return: Location of the command.
 */
char *_whch(char *command, char **_env)
{
	/* Declare variables for path traversal */
	char *path_name, *ptrpath, *tkn_path, *directory;
	int length_dir, length_cmd, index;
	struct stat st;
/* Get the PATH environment variable */
	path_name = get_environ("PATH", _env);
	if (path_name)
	{
		ptrpath = _strdup(path_name);
		length_cmd = _strlen(command);
		tkn_path = _strtok(ptrpath, ":");
		index = 0;
		while (tkn_path != NULL)
		{
			if (check_cdir(path_name, &index))
				if (stat(command, &st) == 0)
					return (command);
			length_dir = _strlen(tkn_path);
			directory = malloc(length_dir + length_cmd + 2);
			_strcpy(directory, tkn_path);
			_strcat(directory, "/");
			_strcat(directory, command);
			_strcat(directory, "\0");
			if (stat(directory, &st) == 0)
			{
				free(ptrpath);
				return (directory);
			}
			free(directory);
			tkn_path = _strtok(NULL, ":");
		}
		free(ptrpath);
		if (stat(command, &st) == 0)
			return (command);
		return (NULL);
	}
	if (command[0] == '/')
		if (stat(command, &st) == 0)
			return (command);
	return (NULL);
}

/**
 * check_cdir - Checks if ":" is present in the current directory.
 * @filepath: Pointer to a character string representing the filepath.
 * @index: Pointer to an integer representing the index.
 *
 * Return: 1 if the path is searchable in the current directory, 0 otherwise.
 */
int check_cdir(char *filepath, int *index)
{
	 /* Check if the current character is a colon (":") */
	if (filepath[*index] == ':')
		return (1);

	while (filepath[*index] != ':' && filepath[*index])
	{
		*index += 1;
	}

	if (filepath[*index])
		*index += 1;

	/* Current directory not found in the path */
	return (0);
}

/**
 * check_error_command - Verifies if the user has permissions
 *                      to access a command or directory.
 * @dir_dest: Destination directory.
 * @datashell: Data structure.
 *
 * Return: 1 if there is an error, 0 if not.
 */
int check_error_command(char *dir_dest, shll_comm *datashell)
{
	if (dir_dest == NULL)
	{
		/* No path provided, command not found */
		get_err(datashell, 127);
		return (1);
	}

	if (_strcmp(datashell->args[0], dir_dest) != 0)
	{
		/* Check execute permission for the destination directory */
		if (access(dir_dest, X_OK) == -1)
		{
			/* No execute permission, command not found or executable */
			get_err(datashell, 126);
			free(dir_dest);
			return (1);
		}
		free(dir_dest);
	}
	else
	{
		if (access(datashell->args[0], X_OK) == -1)
		{
			get_err(datashell, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * command_exec - Executes command lines.
 * @datashell: Data relevant (args and input).
 *
 * Return: 1 on success.
 */
int command_exec(shll_comm *datashell)
{
	pid_t pidm, wpid;
	int stte, exc;
	char *dir;
	(void)wpid;

	exc = is_exec(datashell);
	if (exc == -1)
		return (1);
	if (exc == 0)
	{
		dir = _whch(datashell->args[0], datashell->_env);
		if (check_error_command(dir, datashell) == 1)
			return (1);
	}

	pidm = fork();
	if (pidm == 0)
	{
		if (exc == 0)
			dir = _whch(datashell->args[0], datashell->_env);
		else
			dir = datashell->args[0];
		execve(dir + exc, datashell->args, datashell->_env);
	}
	else if (pidm < 0)
	{
		perror(datashell->argv[0]);
		return (1);
	}
	else
	{
		do {
			wpid = waitpid(pidm, &stte, WUNTRACED);
		} while (!WIFEXITED(stte) && !WIFSIGNALED(stte));
	}

	datashell->stat = stte / 256;

	return (1);
}

/**
 * is_exec - Determines if a command is an executable.
 * @datashell: Data structure.
 *
 * Return: 0 if it's not an executable, otherwise a positive number.
 */
int is_exec(shll_comm *datashell)
{
	struct stat status;
	int index;
	char *inp;

	inp = datashell->args[0];
	for (index = 0; inp[index]; index++)
	{
		if (inp[index] == '.')
		{
			if (inp[index + 1] == '.')
				return (0);
			if (inp[index + 1] == '/')
				continue;
			else
				break;
		}
		else if (inp[index] == '/' && index != 0)
		{
			if (inp[index + 1] == '.')
				continue;
			index++;
			break;
		}
		else
			break;
	}
	if (index == 0)
		return (0);

	if (stat(inp + index, &status) == 0)
		return (index);
	get_err(datashell, 127);

	return (-1);
}
