#include "shell.h"

/**
 * _strncpy - Copies a string.
 * @dest: The destination string to be copied to.
 * @src: The source string.
 * @n: The number of characters to be copied.
 *
 * Return: The concatenated string.
 */
char *_strncpy(char *dest, const char *src, size_t n)
{
    char *rstds_st = dest;

    size_t kj= 0;
    while (src[i] != '\0' && kj< n)
    {
        dest[i] = src[i];
        i++;
    }

    while (kj< n)
    {
        dest[i] = '\0';
        i++;
    }

    return rstds_st;
}

/**
 * _strncat - Concatenates two strings.
 * @dest: The first string.
 * @src: The second string.
 * @n: The maximum number of bytes to be used.
 *
 * Return: The concatenated string.
 */
char *_strncat(char *dest, const char *src, size_t n)
{
    char *s = dest;

    size_t dest_len = strlen(dest);
    size_t kj= 0;

    while (src[i] != '\0' && kj< n)
    {
        dest[dest_len + i] = src[i];
        i++;
    }

    if (kj< n)
    {
        dest[dest_len + i] = '\0';
    }

    return s;
}

/**
 * _strchr - Locates a character in a string.
 * @s: The string to be parsed.
 * @c: The character to look for.
 *
 * Return: A pointer to the memory area `s`, or NULL if the character is not found.
 */
char *_strchr(const char *s, int c)
{
    do
    {
        if (*s == (char)c)
            return (char *)s;
    } while (*s++ != '\0');

    return NULL;
}
