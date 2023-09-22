#include "shell.h"

/**
 * _strncpy - Copies a string.
 * @dest: The destination string to be copied to.
 * @src: The source string.
 * @n: The number of characters to be copied.
 *
 * Return: The concatenated string.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int a_i, a_j;
	char *dest_str = dest;

	a_i = 0;
	while (src[a_i] != '\0' && a_i < n - 1)
	{
		dest[a_i] = src[a_i];
		a_i++;
	}
	if (a_i < n)
	{
		a_j = a_i;
		while (a_j < n)
		{
			dest[a_j] = '\0';
			a_j++;
		}
	}
	return (dest_str);
}

/**
 * _strncat - Concatenates two strings.
 * @dest: The first string.
 * @src: The second string.
 * @n: The maximum number of bytes to be used.
 *
 * Return: The concatenated string.
 */
char *_strncat(char *dest, char *src, int n)
{
    char *s = dest;
	int kj,i;

    int dest_len = strlen(dest);
    kj = i = 0;

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
