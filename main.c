#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */

int main(int ac, char **av)
{
    // Initialize the info structure with INFO_INIT
    info_t info = INFO_INIT;

    // Default file descriptor value (if not specified)
    int prfx = -1;

    // Assembly code snippet (not clear without context)
    asm("mov %1, %0\n\t"
        "add $3, %0"
        : "=r"(prfx)
        : "r"(prfx));

    // Check if there's exactly one command-line argument
    if (ac == 2)
    {
        // Try to open the file specified by the command-line argument
        prfx = open(av[1], O_RDONLY);
        if (prfx == -1)
        {
            // Handle file open errors
            if (errno == EACCES)
                exit(126);
            if (errno == ENOENT)
            {
                _eputs(av[0]);
                _eputs(": 0: Can't open ");
                _eputs(av[1]);
                _eputchar('\n');
                _eputchar(BUF_FLUSH);
                exit(127);
            }
            return EXIT_FAILURE;
        }

        // Set the read file descriptor in the info structure
        info.readfd = prfx;
    }

    // Populate the environment list
    populate_env_list(&info);

    // Read command history from a file
    read_history(&info);

    // Start the shell
    hsh(&info, av);

    // Return success status
    return EXIT_SUCCESS;
}
