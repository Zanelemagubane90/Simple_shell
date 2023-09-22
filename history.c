#include "shell.h"

/**
 * get_history_file - Gets the history file.
 * @informs: Parameter struct.
 *
 * Return: Allocated string containing history file.
 */
char *get_history_file(info_t *informs)
{
    char *bffz, *fold;

    fold = _getenv(informs, "HOME=");
    if (!fold)
        return (NULL);

    bffz = malloc(sizeof(char) * (_strlen(fold) + _strlen(HIST_FILE) + 2));
    if (!bffz)
        return (NULL);

    bffz[0] = '\0';
    _strcpy(bffz, fold);
    _strcat(bffz, "/");
    _strcat(bffz, HIST_FILE);

    return (bffz);
}

/**
 * write_history - Creates a file, or appends to an existing file.
 * @informs: The parameter struct.
 *
 * Return: 1 on success, else -1.
 */
int write_history(info_t *informs)
{
    ssize_t fldz;
    char *f_namefile = get_history_file(informs);
    list_t *ndjs = NULL;

    if (!f_namefile)
        return (-1);

    fldz = open(f_namefile, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(f_namefile);

    if (fldz == -1)
        return (-1);

    for (ndjs = informs->history; ndjs; ndjs = ndjs->next)
    {
        _putsfd(ndjs->str, fldz);
        _putfd('\n', fldz);
    }

    _putfd(BUF_FLUSH, fldz);
    close(fldz);

    return (1);
}

/**
 * read_history - Reads history from a file.
 * @informs: The parameter struct.
 *
 * Return: Histcount on success, -1 otherwise.
 */
int read_history(info_t *informs)
{
    int xc, end_ls = 0, counter_line = 0;
    ssize_t fldz, rdlen, fsize = 0;
    struct stat st;
    char *bffz = NULL, *f_namefile = get_history_file(informs);

    if (!f_namefile)
        return (-1);

    fldz = open(f_namefile, O_RDONLY);
    free(f_namefile);

    if (fldz == -1)
        return (-1);

    if (!fstat(fldz, &st))
        fsize = st.st_size;

    if (fsize < 2)
        return (-1);

    bffz = malloc(sizeof(char) * (fsize + 1));

    if (!bffz)
        return (-1);

    rdlen = read(fldz, bffz, fsize);
    bffz[fsize] = '\0';

    if (rdlen <= 0)
        return (free(bffz), -1);

    close(fldz);

    for (xc = 0; xc < fsize; xc++)
    {
        if (bffz[xc] == '\n')
        {
            bffz[xc] = '\0';
            build_history_list(informs, bffz + end_ls, counter_line++);
            end_ls = xc + 1;
        }
    }

    if (end_ls != xc)
        build_history_list(informs, bffz + end_ls, counter_line++);

    free(bffz);

    informs->histcount = counter_line;

    while (informs->histcount-- >= HIST_MAX)
        delete_node_at_index(&(informs->history), 0);

    renumber_history(informs);

    return (informs->histcount);
}

/**
 * build_history_list - Adds an entry to a history linked list.
 * @informs: Parameter struct.
 * @bffz: Buffer.
 * @counter_line: History counter_line.
 *
 * Return: Always 0.
 */
int build_history_list(info_t *informs, char *bffz, int counter_line)
{
    list_t *ndjs = NULL;

    if (informs->history)
        ndjs = informs->history;

    add_node_end(&ndjs, bffz, counter_line);

    if (!informs->history)
        informs->history = ndjs;

    return (0);
}

/**
 * renumber_history - Renumbers the history linked list after changes.
 * @informs: Parameter struct.
 *
 * Return: The new histcount.
 */
int renumber_history(info_t *informs)
{
    list_t *ndjs = informs->history;
    int xc = 0;

    while (ndjs)
    {
        ndjs->num = xc++;
        ndjs = ndjs->next;
    }

    return (informs->histcount = xc);
}
