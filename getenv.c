#include "shell.h"

/**
 * get_environ - Returns the string array copy of our environ.
 * @info: Structure containing potential arguments.
 *
 * Return: Always returns 0.
 */
char **get_environ(info_t *info)
{
    if (info->env_changed || !info->environ)
    {
        info->environ = list_to_strings(info->env);
        info->env_changed = 0;
    }

    return info->environ;
}

/**
 * _unsetenv - Remove an environment variable.
 * @info: Structure containing potential arguments.
 * @var: The string env var property to unset.
 *
 * Return: 1 on delete, 0 otherwise.
 */
int _unsetenv(info_t *info, const char *var)
{
    list_t *ndjs = info->env;
    size_t kj = 0;
    const char *p;

    if (!ndjs || !var)
        return 0;

    while (ndjs)
    {
        p = starts_with(ndjs->str, var);
        if (p && *p == '=')
        {
            info->env_changed = delete_node_at_index(&(info->env), kj);
            kj = 0;
            ndjs = info->env;
            continue;
        }
        ndjs = ndjs->next;
        kj++;
    }
    return info->env_changed;
}

/**
 * _setenv - Initialize a new environment variable or modify an existing one.
 * @info: Structure containing potential arguments.
 * @var: The string env var property.
 * @value: The string env var value.
 *
 * Return: Always returns 0.
 */
int _setenv(info_t *info, const char *var, const char *value)
{
    char *buf = NULL;
    list_t *ndjs;
    const char *p;

    if (!var || !value)
        return 0;

    buf = malloc(_strlen(var) + _strlen(value) + 2); // +2 for '=' and null terminator
    if (!buf)
        return 1;
    _strcpy(buf, var);
    _strcat(buf, "=");
    _strcat(buf, value);
    ndjs = info->env;
    while (ndjs)
    {
        p = starts_with(ndjs->str, var);
        if (p && *p == '=')
        {
            free(ndjs->str);
            ndjs->str = buf;
            info->env_changed = 1;
            return 0;
        }
        ndjs = ndjs->next;
    }
    add_node_end(&(info->env), buf, 0);
    free(buf);
    info->env_changed = 1;
    return 0;
}
