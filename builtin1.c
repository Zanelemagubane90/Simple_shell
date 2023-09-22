#include "shell.h"

/**
 * _myhistory - Displays the history list, one command per line, preceded
 *              by line numbers, starting at 0.
 * @info: Structure containing potential arguments.
 *
 * Return: Always returns 0.
 */
int _myhistory(info_t *info)
{
    print_list(info->history);
    return 0;
}

/**
 * unset_alias - Unsets an alias by removing it from the alias list.
 * @info: Parameter struct.
 * @str: The string alias to unset.
 *
 * Return: Always returns 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *str)
{
    char *pps, c;
    int ret;

    pps = _strchr(str, '=');
    if (!pps)
        return 1;
    c = *pps;
    *pps = '\0';
    ret = delete_node_at_index(&(info->alias),
                               get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
    *pps = c;
    return ret;
}

/**
 * set_alias - Sets an alias to a string.
 * @info: Parameter struct.
 * @str: The string alias to set.
 *
 * Return: Always returns 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *str)
{
    char *pps;

    pps = _strchr(str, '=');
    if (!pps)
        return 1;
    if (!*++pps)
        return unset_alias(info, str);

    unset_alias(info, str);
    return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Prints an alias string.
 * @node: The alias node to print.
 *
 * Return: Always returns 0 on success, 1 on error.
 */
int print_alias(list_t *node)
{
    char *pps = NULL, *a = NULL;

    if (node)
    {
        pps = _strchr(node->str, '=');
        for (a = node->str; a <= pps; a++)
            _putchar(*a);
        _putchar('\'');
        _puts(pps + 1);
        _puts("'\n");
        return 0;
    }
    return 1;
}

/**
 * _myalias - Mimics the alias builtin (man alias).
 * @info: Structure containing potential arguments.
 *
 * Return: Always returns 0.
 */
int _myalias(info_t *info)
{
    int i = 0;
    list_t *node = NULL;
    char *pps = NULL;

    if (info->argc == 1)
    {
        node = info->alias;
        while (node)
        {
            print_alias(node);
            node = node->next;
        }
        return 0;
    }
    for (i = 1; info->argv[i]; i++)
    {
        pps = _strchr(info->argv[i], '=');
        if (pps)
            set_alias(info, info->argv[i]);
        else
            print_alias(node_starts_with(info->alias, info->argv[i], '='));
    }

    return 0;
}
