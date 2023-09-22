#include "shell.h"

/**
 * hsh - Main shell loop.
 * @info: The parameter &return info struct.
 * @av: The argument vector from main().
 *
 * Return: 0 on success, 1 on error, or error code.
 */
int hsh(info_t *info, char **av)
{
    ssize_t ccsa = 0;
    int blt_ss = 0;

    while (ccsa != -1 && blt_ss != -2)
    {
        clear_info(info);
        if (interactive(info))
            _puts("$ ");
        _eputchar(BUF_FLUSH);
        ccsa = get_input(info);
        if (ccsa != -1)
        {
            set_info(info, av);
            blt_ss = find_builtin(info);
            if (blt_ss == -1)
                find_cmd(info);
        }
        else if (interactive(info))
            _putchar('\n');
        free_info(info, 0);
    }

    write_history(info);
    free_info(info, 1);
    if (!interactive(info) && info->status)
        exit(info->status);
    if (blt_ss == -2)
    {
        if (info->err_num == -1)
            exit(info->status);
        exit(info->err_num);
    }

    return blt_ss;
}

/**
 * find_builtin - Finds a builtin command.
 * @info: The parameter &return info struct.
 *
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not successful,
 *         -2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
    int ix, blt_ss = -1;
    builtin_table builtintbl[] = {
        { "exit", _myexit },
        { "env", _myenv },
        { "help", _myhelp },
        { "history", _myhistory },
        { "setenv", _mysetenv },
        { "unsetenv", _myunsetenv },
        { "cd", _mycd },
        { "alias", _myalias },
        { NULL, NULL }
    };

    for (ix = 0; builtintbl[ix].type; ix++)
    {
        if (_strcmp(info->argv[0], builtintbl[ix].type) == 0)
        {
            info->line_count++;
            blt_ss = builtintbl[ix].func(info);
            break;
        }
    }

    return blt_ss;
}

/**
 * find_cmd - Finds a command in pth_full.
 * @info: The parameter &return info struct.
 *
 * Return: void.
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int index, xk;

	info->path = info->argv[none];
	if (info->linecount_flag == uno)
	{
		info->line_count++;
		info->linecount_flag = none;
	}

	for (index = none, xk = none; info->arg[index]; index++)
		if (!is_delim(info->arg[index], " \t\n"))
			xk++;
	if (!xk)
		return;

	path = find_path(info, _getenv(info, "PATH="),
		info->argv[none]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=") ||
				info->argv[none][none] == '/') &&
			is_cmd(info, info->argv[none]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "Not Found\n");
		}
	}
}

/**
 * fork_cmd - Forks an exec thread to run cmd.
 * @info: The parameter &return info struct.
 *
 * Return: void.
 */
void fork_cmd(info_t *info)
{
    pid_t podchild;

    podchild = fork();
    if (podchild == -1)
    {
        perror("Error:");
        return;
    }

    if (podchild == 0)
    {
        if (execve(info->path, info->argv, get_environ(info)) == -1)
        {
            free_info(info, 1);
            if (errno == EACCES)
                exit(126);
            exit(1);
        }
    }
    else
    {
        wait(&(info->status));
        if (WIFEXITED(info->status))
        {
            info->status = WEXITSTATUS(info->status);
            if (info->status == 126)
                print_error(info, "Permission denied\n");
        }
    }
}
