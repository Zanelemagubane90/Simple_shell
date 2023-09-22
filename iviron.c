#include "shell.h"

/**
 * _myenv - Prints the current environment.
 * @informs: Parameter struct.
 *
 * Return: Always 0.
 */
int _myenv(info_t *informs)
{
    print_list_str(informs->env);
    return (0);
}

/**
 * _getenv - Gets the value of an environment variable.
 * @informs: Parameter struct.
 * @name: Env variable name.
 *
 * Return: The value of the environment variable or NULL if not found.
 */
char *_getenv(info_t *informs, const char *name)
{
    list_t *ndjs = informs->env;
    char *var_env;

    while (ndjs)
    {
        var_env = starts_with(ndjs->str, name);
        if (var_env && *var_env)
            return (var_env);
        ndjs = ndjs->next;
    }

    return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable or modify an existing one.
 * @informs: Parameter struct.
 *
 * Return: Always 0.
 */
int _mysetenv(info_t *informs)
{
    if (informs->argc != 3)
    {
        _eputs("Incorrect number of arguments\n");
        return (1);
    }

    if (_setenv(informs, informs->argv[1], informs->argv[2]) != 0)
        return (1);

    return (0);
}

/**
 * _myunsetenv - Remove an environment variable.
 * @informs: Parameter struct.
 *
 * Return: Always 0.
 */
int _myunsetenv(info_t *informs)
{
    int pint_s;

    if (informs->argc == 1)
    {
        _eputs("Too few arguments.\n");
        return (1);
    }

    for (pint_s = 1; pint_s <= informs->argc; pint_s++)
        _unsetenv(informs, informs->argv[pint_s]);

    return (0);
}

/**
 * populate_env_list - Populates the environment linked list.
 * @informs: Parameter struct.
 *
 * Return: Always 0.
 */
int populate_env_list(info_t *informs)
{
    list_t *ndjs = NULL;
    size_t pint_s;

    for (pint_s = 0; environ[pint_s]; pint_s++)
        add_node_end(&ndjs, environ[pint_s], 0);

    informs->env = ndjs;
    return (0);
}
