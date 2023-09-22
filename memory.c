#include "shell.h"

/**
 * bfree - frees a pointer and NULLs the address
 * @index: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */

int bfree(void **index)
{
	if (index && *index)
	{
		free(*index);
		*index = NULL;
		return (uno);
	}
	return (none);
}
