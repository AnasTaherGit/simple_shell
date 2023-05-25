#include "shell.h"

/**
 * build_cmd_path - builds the full path of a command
 * @dir: directory
 * @cmd: command
 * Return: full path
 */
char *build_cmd_path(char *dir, char *cmd)
{
	size_t size = _strlen(dir) + _strlen(cmd) + 2;
	char *cmd_path = malloc(sizeof(char) * size);

	if (cmd_path == NULL)
		return (NULL);

	_strcpy(cmd_path, dir);
	_strcat(cmd_path, "/");
	_strcat(cmd_path, cmd);

	return (cmd_path);
}
/**
 * get_path_directories - gets the directories in the PATH variable
 * @path_env: PATH variable
 * Return: array of directories
 */

char **get_path_directories(char *path_env)
{
	char **path_dirs = NULL;
	char *path_copy = _strdup(path_env);

	path_dirs = _get_tokens(path_copy, PATH_DELIM);
	free(path_copy);

	return (path_dirs);
}
/**
 * get_full_path - gets the full path of a command
 * @cmd: command
 * Return: full path
 */
char *get_full_path(char *cmd)
{
	char *path_env = _getenv("PATH");
	char *full_path = NULL;
	char **paths = get_path_directories(path_env);
	char *temp_path = NULL;
	int i = 0;

	for (i = 0; paths[i] != NULL; i++)
	{
		temp_path = _strdup(paths[i]);
		full_path = build_cmd_path(temp_path, cmd);
		free(temp_path);

		if (access(full_path, X_OK) == 0)
		{
			/*iter_free(paths);*/
			free_null_terminated_array(paths);
			return (full_path);
		}
		free(full_path);
	}

	free_null_terminated_array(paths);
	return (NULL);
}
/**
 * _getenv - gives the value of a variable
 * @name: name of the variable
 * Return: the value of the variable
 */

char *_getenv(char *name)
{
	char **env = environ;
	int i = 0;

	size_t name_len = _strlen(name);

	for (i = 0; env[i] != NULL; i++)
	{
		if (_strncmp(name, env[i], name_len) == 0 && env[i][name_len] == '=')
		{
			return (&env[i][name_len + 1]);
		}
	}

	return (NULL);
}
