#include "shell.h"

/**
 * clear_info - Initializes an info_t struct.
 * @info: Struct address to be cleared.
 */
void clear_info(info_t *info)
{
    info->arg = NULL;
    info->argv = NULL;
    info->path = NULL;
    info->argc = 0;
}

/**
 * set_info - Initializes an info_t struct with provided arguments.
 * @info: Struct address to be initialized.
 * @av: Argument vector.
 */
void set_info(info_t *info, char **av)
{
    int v = 0;

    info->fname = av[0];
    if (info->arg)
    {
        info->argv = strtow(info->arg, " \t");
        if (!info->argv)
        {
            info->argv = malloc(sizeof(char *) * 2);
            if (info->argv)
            {
                info->argv[0] = _strdup(info->arg);
                info->argv[1] = NULL;
            }
        }
        for (v = 0; info->argv && info->argv[v]; v++)
            ;
        info->argc = v;

        replace_alias(info);
        replace_vars(info);
    }
}

/**
 * free_info - Frees fields of the info_t struct.
 * @info: Struct address to be freed.
 * @all: If true, frees all fields; otherwise, frees only specific fields.
 */
void free_info(info_t *info, int all)
{
    ffree(info->argv);
    info->argv = NULL;
    info->path = NULL;

    if (all)
    {
        if (info->cmd_buf)
        {
            bfree((void **)info->cmd_buf);
        }

        if (info->env)
        {
            free_list(&(info->env));
        }

        if (info->history)
        {
            free_list(&(info->history));
        }

        if (info->alias)
        {
            free_list(&(info->alias));
        }

        if (info->environ)
        {
            ffree(info->environ);
            info->environ = NULL;
        }

        if (info->readfd > 2)
        {
            close(info->readfd);
        }

        if (!info->cmd_buf)
        {
            free(info->arg);
        }

        _putchar(BUF_FLUSH);
    }
}
