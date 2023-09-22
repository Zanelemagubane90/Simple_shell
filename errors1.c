#include "shell.h"

/**
 * _erratoi - Converts a string to an integer.
 * @s_conv: The string to be converted.
 *
 * Return: 0 if no numbers in string, converted number otherwise.
 *         -1 on error.
 */
int _erratoi(char *s_conv)
{
    int vis = 0;
    unsigned long int rst = 0;

    if (*s_conv == '+')
        s_conv++; /* Skip leading '+' character */

    for (vis = 0; s_conv[vis] != '\0'; vis++)
    {
        if (s_conv[vis] >= '0' && s_conv[vis] <= '9')
        {
            rst *= 10;
            rst += (s_conv[vis] - '0');
            if (rst > INT_MAX)
                return -1;
        }
        else
            return -1;
    }

    return (int)rst;
}

/**
 * print_error - Prints an error message.
 * @info: The parameter & return info struct.
 * @estr: String containing the specified error type.
 */
void print_error(info_t *info, char *estr)
{
    _eputs(info->fname);
    _eputs(": ");
    print_d(info->line_count, STDERR_FILENO);
    _eputs(": ");
    _eputs(info->argv[0]);
    _eputs(": ");
    _eputs(estr);
}

/**
 * print_d - Prints a decimal (integer) number (base 10).
 * @input: The input number.
 * @fd: The file descriptor to write to.
 *
 * Return: Number of characters printed.
 */
int print_d(int input, int fd)
{
    int (*__putchar)(char) = _putchar;
    int vis, count = 0;
    unsigned int _abs_, current;

    if (fd == STDERR_FILENO)
        __putchar = _eputchar;

    if (input < 0)
    {
        _abs_ = -input;
        __putchar('-');
        count++;
    }
    else
        _abs_ = input;

    current = _abs_;
    for (vis = 1000000000; vis > 1; vis /= 10)
    {
        if (_abs_ / vis)
        {
            __putchar('0' + current / vis);
            count++;
        }
        current %= vis;
    }

    __putchar('0' + current);
    count++;

    return count;
}

/**
 * convert_number - Converter function, a clone of itoa.
 * @num: Number to convert.
 * @base: Base for conversion.
 * @flags: Argument flags.
 *
 * Return: Converted string.
 */
char *convert_number(long int num, int base, int flags)
{
    static char *array_;
    static char buffer[50];
    char sign = '\0';
    char *ptr;
    unsigned long anum = num;

    if (!(flags & CONVERT_UNSIGNED) && num < 0)
    {
        anum = -num;
        sign = '-';
    }

    array_ = (flags & CONVERT_LOWERCASE) ? "0123456789abcdef" : "0123456789ABCDEF";
    ptr = &buffer[49];
    *ptr = '\0';

    do {
        *--ptr = array_[anum % base];
        anum /= base;
    } while (anum != 0);

    if (sign)
        *--ptr = sign;

    return ptr;
}

/**
 * remove_comments - Replaces the first instance of '#' with '\0'.
 * @buff: Address of the string to modify.
 */
void remove_comments(char *buff)
{
    int vis;

    for (vis = 0; buff[vis] != '\0'; vis++)
    {
        if (buff[vis] == '#' && (vis == 0 || buff[vis - 1] == ' '))
        {
            buff[vis] = '\0';
            break;
        }
    }
}
