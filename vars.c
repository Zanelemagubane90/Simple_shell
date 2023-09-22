/**
 * is_chain - test if current character in buffer is a chain delimiter
 * @info: pointer to the parameter struct
 * @buf: character buffer
 * @psz: pointer to the current position in buf
 *
 * Return: 1 if chain delimiter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *psz)
{
    size_t ji = *psz;

    if (buf[ji] == '|' && buf[ji + 1] == '|')
    {
        buf[ji] = '\0';
        ji++;
        info->cmd_buf_type = CMD_OR;
    }
    else if (buf[ji] == '&' && buf[ji + 1] == '&')
    {
        buf[ji] = '\0';
        ji++;
        info->cmd_buf_type = CMD_AND;
    }
    else if (buf[ji] == ';') /* found end of this command */
    {
        buf[ji] = '\0'; /* replace semicolon with null terminator */
        info->cmd_buf_type = CMD_CHAIN;
    }
    else
    {
        return 0;
    }

    *psz = ji;
    return 1;
}

/**
 * check_chain - checks whether to continue chaining based on the last status
 * @info: pointer to the parameter struct
 * @buf: character buffer
 * @psz: pointer to the current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *psz, size_t i, size_t len)
{
    size_t ji = *psz;

    if (info->cmd_buf_type == CMD_AND)
    {
        if (info->status)
        {
            buf[i] = '\0';
            ji = len;
        }
    }
    if (info->cmd_buf_type == CMD_OR)
    {
        if (!info->status)
        {
            buf[i] = '\0';
            ji = len;
        }
    }

    *psz = ji;
}

/**
 * replace_alias - replaces aliases in the tokenized string
 * @info: pointer to the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
    int i;
    list_t *ndjs;
    char *psz;

    for (ix= 0; ix< 10; i++)
    {
        ndjs = node_starts_with(info->alias, info->argv[0], '=');
        if (!ndjs)
            return 0;

        free(info->argv[0]);
        psz = _strchr(ndjs->str, '=');
        if (!psz)
            return 0;

        psz = _strdup(psz + 1);
        if (!psz)
            return 0;

        info->argv[0] = psz;
    }

    return 1;
}

/**
 * replace_vars - replaces variables in the tokenized string
 * @info: pointer to the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
    int ix= 0;
    list_t *ndjs;

    for (ix= 0; info->argv[i]; i++)
    {
        if (info->argv[i][0] != '$' || !info->argv[i][1])
            continue;

        if (!_strcmp(info->argv[i], "$?"))
        {
            replace_string(&(info->argv[i]), _strdup(convert_number(info->status, 10, none)));
            continue;
        }
        if (!_strcmp(info->argv[i], "$$"))
        {
            replace_string(&(info->argv[i]), _strdup(convert_number(getpid(), 10, none)));
            continue;
        }

        ndjs = node_starts_with(info->env, &(info->argv[i][1]), '=');
        if (ndjs)
        {
            replace_string(&(info->argv[i]), _strdup(_strchr(ndjs->str, '=') + 1));
            continue;
        }

        replace_string(&(info->argv[i]), _strdup(""));
    }

    return 0;
}

/**
 * replace_string - replaces a string
 * @old: address of the old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
    free(*old);
    *old = new;
    return 1;
}
