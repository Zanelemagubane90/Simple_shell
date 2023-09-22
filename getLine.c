#include "shell.h"

/**
 * input_buf - Buffers chained commands.
 * @informs: Parameter struct.
 * @buf: Address of buffer.
 * @len: Address of len variable.
 *
 * Return: Bytes read.
 */
ssize_t input_buf(info_t *informs, char **buf, size_t *len)
{
    ssize_t szi = 0;
    size_t vpsa = 0;

    if (!*len) /* If nothing left in the buffer, fill it */
    {
        /*bfree((void **)informs->cmd_buf);*/
        free(*buf);
        *buf = NULL;
        signal(SIGINT, sigintHandler);
#if USE_GETLINE
        szi = getline(buf, &vpsa, stdin);
#else
        szi = _getline(informs, buf, &vpsa);
#endif
        if (szi > 0)
        {
            if ((*buf)[szi - 1] == '\n')
            {
                (*buf)[szi - 1] = '\0'; /* Remove trailing newline */
                szi--;
            }
            informs->linecount_flag = 1;
            remove_comments(*buf);
            build_history_list(informs, *buf, informs->histcount++);
            /* if (_strchr(*buf, ';')) is this a command chain? */
            {
                *len = szi;
                informs->cmd_buf = buf;
            }
        }
    }
    return szi;
}

/**
 * get_input - Gets a line minus the newline.
 * @informs: Parameter struct.
 *
 * Return: Bytes read.
 */
ssize_t get_input(info_t *informs)
{
    static char *buf; /* The ';' command chain buffer */
    static size_t i, j, len;
    ssize_t szi = 0;
    char **buf_p = &(informs->arg), *p;

    _putchar(BUF_FLUSH);
    szi = input_buf(informs, &buf, &len);
    if (szi == -1) /* EOF */
        return -1;
    if (len) /* We have commands left in the chain buffer */
    {
        j = i;       /* Init new iterator to the current buf position */
        p = buf + i; /* Get pointer for return */

        check_chain(informs, buf, &j, i, len);
        while (j < len) /* Iterate to semicolon or end */
        {
            if (is_chain(informs, buf, &j))
                break;
            j++;
        }

        i = j + 1; /* Increment past nulled ';' */
        if (i >= len) /* Reached the end of the buffer? */
        {
            i = len = 0; /* Reset position and length */
            informs->cmd_buf_type = CMD_NORM;
        }

        *buf_p = p;         /* Pass back pointer to the current command position */
        return _strlen(p); /* Return length of the current command */
    }

    *buf_p = buf; /* Else not a chain, pass back buffer from _getline() */
    return szi;      /* Return length of the buffer from _getline() */
}

/**
 * read_buf - Reads a buffer.
 * @informs: Parameter struct.
 * @buf: Buffer.
 * @i: Size.
 *
 * Return: szi
 */
ssize_t read_buf(info_t *informs, char *buf, size_t *i)
{
    ssize_t szi = 0;

    if (*i)
        return 0;
    szi = read(informs->readfd, buf, READ_BUF_SIZE);
    if (szi >= 0)
        *i = szi;
    return szi;
}

/**
 * _getline - Gets the next line of input from STDIN.
 * @informs: Parameter struct.
 * @ptr: Address of pointer to buffer, preallocated or NULL.
 * @length: Size of preallocated ptr buffer if not NULL.
 *
 * Return: s
 */
int _getline(info_t *informs, char **ptr, size_t *length)
{
    static char buf[READ_BUF_SIZE];
    static size_t i, len;
    size_t k;
    ssize_t szi = 0, s = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *ptr;
    if (p && length)
        s = *length;
    if (i == len)
        i = len = 0;

    szi = read_buf(informs, buf, &len);
    if (szi == -1 || (szi == 0 && len == 0))
        return -1;

    c = _strchr(buf + i, '\n');
    k = c ? 1 + (size_t)(c - buf) : len;
    new_p = _realloc(p, s, s ? s + k : k + 1); /* +1 for null terminator */
    if (!new_p) /* MALLOC FAILURE! */
        return p ? (free(p), -1) : -1;

    if (s)
        _strncat(new_p, buf + i, k - i);
    else
        _strncpy(new_p, buf + i, k - i + 1); /* +1 for null terminator */

    s += k - i;
    i = k;
    p = new_p;

    if (length)
        *length = s;
    *ptr = p;
    return s;
}

/**
 * sigintHandler - Blocks ctrl-C.
 * @sig_num: The signal number.
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused)) int sig_num)
{
    _puts("\n");
    _puts("$ ");
    _putchar(BUF_FLUSH);
}
