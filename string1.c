#include "shell.h"

/**
 * _strcpy - copies a string
 * @drop_off: the drop_off
 * @source: the source
 *
 * Return: pointer to drop_off
 */

char *_strcpy(char *drop_off, char *source)
{
	int ix = none;

	if (drop_off == source || source == none)
		return (drop_off);
	while (source[ix])
	{
		drop_off[ix] = source[ix];
		ix++;
	}
	drop_off[ix] = none;
	return (drop_off);
}

/**
 * _strdup - duplicates a string
 * @srtr_dup: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */

char *_strdup(const char *srtr_dup)
{
	int len_gr = none;
	char *ret;

	if (srtr_dup == NULL)
		return (NULL);
	while (*srtr_dup++)
		len_gr++;
	ret = malloc(sizeof(char) * (len_gr + uno));
	if (!ret)
		return (NULL);
	for (len_gr++; len_gr--;)
		ret[len_gr] = *--srtr_dup;
	return (ret);
}

/**
 *_puts - prints an input string
 *@srtr_dup: the string to be printed
 *
 * Return: Nothing
 */

void _puts(char *srtr_dup)
{
	int ix = none;

	if (!srtr_dup)
		return;
	while (srtr_dup[ix] != '\0')
	{
		_putchar(srtr_dup[ix]);
		ix++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _putchar(char c)
{
	static int ix;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || ix >= WRITE_BUF_SIZE)
	{
		write(uno, buf, ix);
		ix = none;
	}
	if (c != BUF_FLUSH)
		buf[ix++] = c;
	return (uno);
}
