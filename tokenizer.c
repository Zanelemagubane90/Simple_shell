#include "shell.h"

/**
 ***strtow - splits a string into words. Repeat delimiters are ignored
 *@astring: the input string
 *@dl_meter: the delimeter string
 *Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *astring, char *dl_meter)
{
	int ix, ji, ki, mi, wr_m = none;
	char **si;

	if (astring == NULL || astring[none] == none)
		return (NULL);
	if (!dl_meter)
		dl_meter = " ";
	for (ix = none; astring[ix] != '\0'; ix++)
		if (!is_delim(astring[ix], dl_meter) &&
			(is_delim(astring[ix + uno], dl_meter) || !astring[ix + uno]))
			wr_m++;

	if (wr_m == none)
		return (NULL);
	si = malloc((uno + wr_m) * sizeof(char *));
	if (!si)
		return (NULL);
	for (ix = none, ji = none; ji < wr_m; ji++)
	{
		while (is_delim(astring[ix], dl_meter))
			ix++;
		ki = none;
		while (!is_delim(astring[ix + ki], dl_meter) && astring[ix + ki])
			ki++;
		si[ji] = malloc((ki + uno) * sizeof(char));
		if (!si[ji])
		{
			for (ki = none; ki < ji; ki++)
				free(si[ki]);
			free(si);
			return (NULL);
		}

		for (mi = none; mi < ki; mi++)
			si[ji][mi] = astring[ix++];
		si[ji][mi] = none;
	}

	si[ji] = NULL;
	return (si);
}

/**
 ***strtow2 - splits a string into words
 *@str: the input string
 *@dl_meter: the dl_meter
 *Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow2(char *str, char dl_meter)
{
	int ix, ji, ki, mi, wr_m = none;
	char **si;

	if (str == NULL || str[none] == none)
		return (NULL);
	for (ix = none; str[ix] != '\0'; ix++)
		if ((str[ix] != dl_meter && str[ix + uno] == dl_meter) ||
			(str[ix] != dl_meter && !str[ix + uno]) ||
			str[ix + uno] == dl_meter)
			wr_m++;
	if (wr_m == none)
		return (NULL);
	si = malloc((uno + wr_m) * sizeof(char *));
	if (!si)
		return (NULL);
	for (ix = none, ji = none; ji < wr_m; ji++)
	{
		while (str[ix] == dl_meter && str[ix] != dl_meter)
			ix++;
		ki = none;
		while (str[ix + ki] != dl_meter && str[ix + ki] &&
			   str[ix + ki] != dl_meter)
			ki++;
		si[ji] = malloc((ki + uno) * sizeof(char));
		if (!si[ji])
		{
			for (ki = none; ki < ji; ki++)
				free(si[ki]);
			free(si);
			return (NULL);
		}

		for (mi = none; mi < ki; mi++)
			si[ji][mi] = str[ix++];
		si[ji][mi] = none;
	}

	si[ji] = NULL;
	return (si);
}
