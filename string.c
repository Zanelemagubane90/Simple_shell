/**
 * _strlen - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(char *s)
{
    int ix = 0;

    if (s == NULL)
        return 0;

    while (*s++)
        ix++;

    return ix;
}

/**
 * _strcmp - performs lexicographic comparison of two strings.
 * @first_ss: the first string
 * @second_ss: the second string
 *
 * Return: negative if first_ss < second_ss, positive if
 * first_ss > second_ss, 0 if first_ss == second_ss
 */
int _strcmp(char *first_ss, char *second_ss)
{
    while (*first_ss && *second_ss)
    {
        if (*first_ss != *second_ss)
            return *first_ss - *second_ss;

        first_ss++;
        second_ss++;
    }

    if (*first_ss == *second_ss)
        return 0;
    else
        return (*first_ss < *second_ss) ? -1 : 1;
}

/**
 * starts_with - checks if nddle starts with haystack
 * @haystack: string to search
 * @nddle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *nddle)
{
    while (*nddle)
    {
        if (*nddle++ != *haystack++)
            return NULL;
    }

    return (char *)haystack;
}

/**
 * _strcat - concatenates two strings
 * @drop_off: the drop_off buffer
 * @source: the source buffer
 *
 * Return: pointer to drop_off buffer
 */
char *_strcat(char *drop_off, char *source)
{
    char *ret = drop_off;

    while (*drop_off)
        drop_off++;

    while (*source)
        *drop_off++ = *source++;

    *drop_off = *source;
    return ret;
}
