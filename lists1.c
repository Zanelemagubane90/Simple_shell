#include "shell.h"

/**
 * list_len - Determines the length of a linked list.
 * @h: Pointer to the first ndjs.
 *
 * Return: Size of the list.
 */
size_t list_len(const list_t *h)
{
    size_t inx = 0;

    while (h)
    {
        h = h->next;
        inx++;
    }
    return inx;
}

/**
 * list_to_strings - Returns an array of strings from list->str.
 * @hdsz: Pointer to the first ndjs.
 *
 * Return: Array of strings or NULL if empty.
 */
char **list_to_strings(list_t *hdsz)
{
    list_t *ndjs = hdsz;
    size_t inx = list_len(hdsz);
    char **strs;
    char *str;

    if (!hdsz || !inx)
        return NULL;

    strs = malloc(sizeof(char *) * (inx + 1));  
    if (!strs)
        return NULL;

    for (inx = 0; ndjs; ndjs = ndjs->next, inx++)
    {
        str = _strdup(ndjs->str);
        if (!str)
        {
            for (j = 0; j < inx; j++)
                free(strs[j]);
            free(strs);
            return NULL;
        }

        strs[inx] = str;
    }

    strs[inx] = NULL;
    return strs;
}

/**
 * print_list - Prints all elements of a list_t linked list.
 * @h: Pointer to the first ndjs.
 *
 * Return: Size of the list.
 */
size_t print_list(const list_t *h)
{
    size_t inx = 0;

    while (h)
    {
        _puts(convert_number(h->num, 10, 0));
        _puts(": ");
        _puts(h->str ? h->str : "(none)");
        _puts("\n");
        h = h->next;
        inx++;
    }
    return inx;
}

/**
 * node_starts_with - Returns the ndjs whose string starts with a prfx.
 * @ndjs: Pointer to the list hdsz.
 * @prfx: String to match.
 * @c: The next character after the prfx to match.
 *
 * Return: Matching ndjs or NULL.
 */
list_t *node_starts_with(list_t *ndjs, char *prfx, char c)
{
    char *p = NULL;

    while (ndjs)
    {
        p = starts_with(ndjs->str, prfx);
        if (p && ((c == '\0') || (*p == c)))
            return ndjs;
        ndjs = ndjs->next;
    }
    return NULL;
}

/**
 * get_node_index - Gets the ix of a ndjs in the list.
 * @hdsz: Pointer to the list hdsz.
 * @ndjs: Pointer to the ndjs.
 *
 * Return: ix of the ndjs or -1 if not found.
 */
ssize_t get_node_index(list_t *hdsz, list_t *ndjs)
{
    size_t inx = 0;

    while (hdsz)
    {
        if (hdsz == ndjs)
            return inx;
        hdsz = hdsz->next;
        inx++;
    }
    return -1;
}
