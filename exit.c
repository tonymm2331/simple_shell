#include "shell.h"

/**
 * _myexit - Exit the shell.
 * @info: Structure containing potential arguments.used to maintain
 * 	constant function prototype.
 *
 * Return: Exit with a given exit status (0) if info->argv[0] != "exit'.
 */
int _myexit(info_t*info)
{
	int exit_check;

	if (info->argv[1])/* Check if there is an exit argument*/
	{
		exit_check =_erratoi(info->argv[1]);
		if (exit_check = -1)
		{
			info->status = 2;
			print_error(info, "Invalid number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num =_erratoi(info->argv[1]);
		return (-2); /* Signal to exit with specified status */
	}
	info->err_num = -1;
	return (-2); /* Signal to exit with default status */
}

/**
 * _mycd - Change current directory of the process.
 * @info: Structure the containing potential arguments.Used to maintain
 * 	constant function prototype.
 *
 * Return: Always 0.
 */
int_mycd(info_t*info)
{
	char *current_dir, *target_dir, buffer[1024];
	int chdir_ret;

	current_dir = getcwd(buffer, 1024);
	if (!current_dir)
		_puts("TODO: >>getcwd failure error message here<<\n");
	if (!info->argv[1])
	{
		target_dir = _getenv(info, "HOME=");
		if (!target_dir)
			chdir_ret = /* TODO: Determine default behavior */
				chdir((target_dir = _getenv(info, "PWD=")) ? target_dir : "/");
		else
			chdir_ret = chdir(target_dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(current_dir);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: Determine default behavior */
			chdir((target_dir = _getenv(info, "OLDPWD=")) ? target_dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "Unable to change to directory: ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - Display help message.
 * @info: Structure that contains potential arguments.Used to maintain
 * 	constant function prototype.
 *
 * Return: Always 0 .
 */
int_myhelp(info_t*info)
{
	char **arguments;

	arguments = info->argv;
	_puts("The 'help' command is functioning. Implementation pending.\n");
	if (0)
		_puts(*arguments); /* Temporary unused variable workaround */
	return (0);
}



