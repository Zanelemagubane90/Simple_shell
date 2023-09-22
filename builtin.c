#include "shell.h"

/**
 * _myexit - Exits the shell.
 * @info: Structure containing potential arguments.
 *
 * Return: Exits with a given exit status (0) if info->argv[0] != "exit".
 */
int _myexit(info_t *info)
{
	int exit_ch;

	if (info->argv[1]) /* If there is an exit argument */
	{
		exit_ch = _strtoi(info->argv[1]);
		if (exit_ch == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return 1;
		}
		info->err_num = exit_ch;
		return -2;
	}
	info->err_num = 1;
	return -2;
}

/**
 * _mycd - Changes the current directory of the process.
 * @info: Structure containing potential arguments.
 *
 * Return: Always returns 0.
 */
int _mycd(info_t *info)
{
	int chdir_result;
	char *current_dir, *new_dir, buffer[1024];

	current_dir = getcwd(buffer, 1024);
	if (!current_dir)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		new_dir = _getenv(info, "HOME=");
		if (!new_dir)
			chdir_result = chdir((new_dir = _getenv(info, "PWD=")) ? new_dir : "/");
		else
			chdir_result = chdir(new_dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(current_dir);
			_putchar('\n');
			return 0;
		}
		_puts(_getenv(info, "OLDPWD="));
		_putchar('\n');
		chdir_result = chdir((new_dir = _getenv(info, "OLDPWD=")) ? new_dir : "/");
	}
	else
		chdir_result = chdir(info->argv[1]);

	if (chdir_result == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]);
		_eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return 0;
}

/**
 * _myhelp - Displays help information.
 * @info: Structure containing potential arguments.
 *
 * Return: Always returns 0.
 */
int _myhelp(info_t *info)
{
	char **arguments_array;

	arguments_array = info->argv;
	_puts("help call works. Function not yet implemented\n");
	if (arguments_array)
		_puts(*arguments_array); /* Temporary att_unused workaround */
	return 0;
}
