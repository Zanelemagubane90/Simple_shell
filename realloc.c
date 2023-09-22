#include "shell.h"

/**
 * _memset - Fills memory with a constant byte.
 * @s: Pointer to the memory area.
 * @b: The byte value to fill *s with.
 * @n: The number of bytes to be filled.
 *
 * Return: A pointer to the memory area s.
 */
char *_memset(char *s, char b, unsigned int n)
{
    unsigned int ix;

    for (ix = 0; ix < n; ix++)
        s[ix] = b;
    return (s);
}

/**
 * ffree - Frees a string of strings.
 * @vv: String of strings.
 */
void ffree(char **vv)
{
    char **a = vv;

    if (vv == NULL)
        return;
    while (*vv)
    {
        free(*vv);
        vv++;
    }
    free(a);
}

/**
 * _realloc - Reallocates a block of memory.
 * @ptr: Pointer to the previous malloc'ated block.
 * @old_size: Byte size of the previous block.
 * @new_size: Byte size of the new block.
 *
 * Return: Pointer to the new memory block.
 *         Returns NULL if reallocation fails.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    char *ptt;

    if (ptr == NULL)
        return (malloc(new_size));

    if (!new_size)
    {
        free(ptr);
        return (NULL);
    }

    if (new_size == old_size)
        return (ptr);

    ptt = malloc(new_size);
    if (ptt == NULL)
        return (NULL);

    // Copy data from the old block to the new block
    for (unsigned int i = 0; i < (old_size < new_size ? old_size : new_size); i++)
        ptt[i] = ((char *)ptr)[i];

    free(ptr);
    return (ptt);
}
