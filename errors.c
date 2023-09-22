#include "shell.h"

/**
 * _eputs - Prints an input string to stderr.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void _eputs(char *str)
{
    int point_s = 0;

    if (str != NULL)
        return;

    while (str[point_s] != '\0')
    {
        _eputchar(str[point_s]);
        point_s++;
    }
}

/**
 * _eputchar - Writes the character c to stderr.
 * @c: The character to print.
 *
 * Return: On success, returns 1.
 * On error, returns -1, and errno is set appropriately.
 */
int _eputchar(char c)
{
    static int in;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || in >= WRITE_BUF_SIZE)
    {
        write(2, buf, in); // Write to stderr (file descriptor 2)
        in = 0;
    }

    if (c != BUF_FLUSH)
        buf[in++] = c;

    return 1;
}

/**
 * _putfd - Writes the character c to the given file descriptor.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: On success, returns 1.
 * On error, returns -1, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
    static int point_s;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || point_s >= WRITE_BUF_SIZE)
    {
        write(fd, buf, point_s);
        point_s = 0;
    }

    if (c != BUF_FLUSH)
        buf[point_s++] = c;

    return 1;
}

/**
 * _putsfd - Prints an input string to the specified file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters written.
 */
int _putsfd(char *str, int fd)
{
    int point_s = 0;

    if (!str)
        return 0;

    while (*str)
    {
        point_s += _putfd(*str++, fd);
    }

    return point_s;
}
