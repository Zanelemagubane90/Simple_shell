#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(const char *path)
{
    struct stat st;

    if (path == NULL || stat(path, &st) == -1)
        return 0;

    return S_ISREG(st.st_mode);
}

/**
 * extract_path_segment - extracts a the_seg from the PATH string
 * @path_str: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: dynamically allocated buffer containing the the_seg
 */
char *extract_path_segment(const char *path_str, int start, int stop)
{
    if (!path_str || start < 0 || stop < start)
        return NULL;

    int length = stop - start;
    char *the_seg = malloc(length + 1);

    if (!the_seg)
        return NULL;

    for (int i = start, j = 0; i < stop; i++, j++) {
        if (path_str[i] != ':')
            the_seg[j] = path_str[i];
        else
            the_seg[j] = '/';
    }

    the_seg[length] = '\0';
    return the_seg;
}

/**
 * find_executable - finds the full path of an executable command in PATH
 * @path_str: the PATH string
 * @cmmd: the command to find
 *
 * Return: full path of cmmd if found, NULL otherwise
 */
char *find_executable(const char *path_str, const char *cmmd)
{
    if (!path_str || !cmmd)
        return NULL;

    if (is_cmd(cmmd))
        return strdup(cmmd);

    int start = 0, stop = 0;
    char *the_seg = NULL;

    while (path_str[start] != '\0') {
        if (path_str[start] == ':')
            start++;
        else {
            stop = start;
            while (path_str[stop] != '\0' && path_str[stop] != ':')
                stop++;
            the_seg = extract_path_segment(path_str, start, stop);
            if (!the_seg)
                return NULL;

            char *path_full = malloc(strlen(the_seg) + strlen(cmmd) + 2);
            if (!path_full) {
                free(the_seg);
                return NULL;
            }

            strcpy(path_full, the_seg);
            strcat(path_full, "/");
            strcat(path_full, cmmd);

            if (is_cmd(path_full)) {
                free(the_seg);
                return path_full;
            }

            free(the_seg);
            free(path_full);
            start = stop;
        }
    }

    return NULL;
}
