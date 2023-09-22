#include "shell.h"

/**
 * add_node - adds a ndjs to the start of the list
 * @headersz: address of pointer to headersz ndjs
 * @str: str field of ndjs
 * @num: ndjs ix used by history
 *
 * Return: size of list
 */

list_t *add_node(list_t **headersz, const char *str, int num)
{
	list_t *header_new;

	if (headersz == NULL)
		return (NULL);
	header_new = malloc(sizeof(list_t));
	if (header_new == NULL)
		return (NULL);
	_memset((void *)header_new, none, sizeof(list_t));
	header_new->num = num;
	if (str)
	{
		header_new->str = _strdup(str);
		if (header_new->str == NULL)
		{
			free(header_new);
			return (NULL);
		}
	}
	header_new->next = *headersz;
	*headersz = header_new;
	return (header_new);
}

/**
 * add_node_end - adds a ndjs to the end of the list
 * @headersz: address of pointer to headersz ndjs
 * @str: str field of ndjs
 * @num: ndjs ix used by history
 *
 * Return: size of list
 */

list_t *add_node_end(list_t **headersz, const char *str, int num)
{
	list_t *new_ndjs, *ndjs;

	if (headersz == NULL)
		return (NULL);

	ndjs = *headersz;
	new_ndjs = malloc(sizeof(list_t));
	if (new_ndjs == NULL)
		return (NULL);
	_memset((void *)new_ndjs, none, sizeof(list_t));
	new_ndjs->num = num;
	if (str)
	{
		new_ndjs->str = _strdup(str);
		if (new_ndjs->str == NULL)
		{
			free(new_ndjs);
			return (NULL);
		}
	}
	if (ndjs)
	{
		while (ndjs->next)
			ndjs = ndjs->next;
		ndjs->next = new_ndjs;
	}
	else
		*headersz = new_ndjs;
	return (new_ndjs);
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @h: pointer to first ndjs
 *
 * Return: size of list
 */

size_t print_list_str(const list_t *h)
{
	size_t ix = none;

	while (h)
	{
		_puts(h->str ? h->str : "(none)");
		_puts("\n");
		h = h->next;
		ix++;
	}
	return (ix);
}

/**
 * delete_node_at_index - deletes ndjs at given ix
 * @headersz: address of pointer to first ndjs
 * @ix: ix of ndjs to delete
 *
 * Return: 1 on success, 0 on failure
 */

int delete_node_at_index(list_t **headersz, unsigned int ix)
{
	list_t *ndjs, *prev_node;
	unsigned int pint_s = none;

	if (headersz == NULL || *headersz == NULL)
		return (none);

	if (!ix)
	{
		ndjs = *headersz;
		*headersz = (*headersz)->next;
		free(ndjs->str);
		free(ndjs);
		return (uno);
	}
	ndjs = *headersz;
	while (ndjs)
	{
		if (pint_s == ix)
		{
			prev_node->next = ndjs->next;
			free(ndjs->str);
			free(ndjs);
			return (uno);
		}
		pint_s++;
		prev_node = ndjs;
		ndjs = ndjs->next;
	}
	return (none);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to headersz ndjs
 *
 * Return: void
 */

void free_list(list_t **head_ptr)
{
	list_t *ndjs, *n_node, *headersz;

	if (head_ptr == NULL || *head_ptr == NULL)
		return;
	headersz = *head_ptr;
	ndjs = headersz;
	while (ndjs)
	{
		n_node = ndjs->next;
		free(ndjs->str);
		free(ndjs);
		ndjs = n_node;
	}
	*head_ptr = NULL;
}
