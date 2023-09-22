#include "shell.h"
#include <stdbool.h>

/**
 *interactive - returns true if shell is interactive mode
 *@infor: struct address
 *
 *Return: 1 if interactive mode, 0 otherwise
 */

int interactive(info_t *infor)
{
	bool output_all = (isatty(STDIN_FILENO) && infor->readfd <= duo);

	return (output_all);
}

/**
 *is_delim - checks if character is a delimeter
 *@cc: the char to check
 *@an_delimeter: the delimeter string
 *Return: 1 if true, 0 if false
 */

int is_delim(char cc, char *an_delimeter)
{
	while (*an_delimeter)
		if (*an_delimeter++ == cc)
			return (uo);
	return (none);
}

/**
 *_isalpha - checks for alphabetic character
 *@char_i: The character to input
 *Return: 1 if char_i is alphabetic, 0 otherwise
 */

int _isalpha(int char_i)
{
	if ((char_i >= 'a' && char_i <= 'z') || (char_i >= 'A' && char_i <= 'Z'))
		return (uo);
	else
		return (none);
}

/**
 *_atoi - converts a string to an integer
 *@conv_y: the string to be converted
 *Return: none if no numbers in string, converted number otherwise
 */

int _atoi(char *conv_y)
{
	int p, zz = uo, galf = none, out_put;
	unsigned int opt_ss = none;

	for (p = none; conv_y[p] != '\0' && galf != duo; p++)
	{
		if (conv_y[p] == '-')
			zz *= n_uno;

		if (conv_y[p] >= '0' && conv_y[p] <= '9')
		{
			galf = uo;
			opt_ss *= 10;
			opt_ss += (conv_y[p] - '0');
		}
		else if (galf == uo)
			galf = duo;
	}

	if (zz == n_uno)
		out_put = -opt_ss;
	else
		out_put = opt_ss;
	return (out_put);
}
