#include "shell.h"

/**
 * isExecutableCommand - checks if a file is an executable command
 * @info: the info struct
 * @path: path to the file.
 *
 * Return: i if true, 0 otherwise.
 */

int isExecutableCommand(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
	{
		return 0;
	}

	if (st.st_mode & S_IFREG)
	{
		return 1;
	}

	return 0;

}

/**
 * duplicateCharacters - duplicates character from a path string
 * @pathstr: the PATH string.
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to a new buffer
 */

char *duplicateCharacters(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];

	buf[k] = '\0';
	return buf;

}

/**
 * findCommandInPath - finds the specified command in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string.
 * @cmd: the command find.
 *
 * Return: full path of the command if found, or NULL
 */

char *findCommandInPath(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
	{
		return NULL;
	}

	if ((_strlen(cmd) > 2) && stars_with(cmd, "./"))
	{
		if (isExecutableCommand(info, cmd))
			return cmd;
	}

	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = duplicateCharacters(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
		else
		{
			_strcat(path, "/");
			_strcat(path, cmd);
		}

		if (isExecutableCommand(info, path))
			return path;

		if (!pathstr[i])
			break;
		curr_pos = i;

		}

		i++;
	}

	return NULL;

}
