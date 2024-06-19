#include "1hreadelf.h"

/**
 * main - The primary function
 * @argc: Number of arguements given
 * @argv: Array of arguments
 * Return: 1 for failure, 0 for success
*/

int main(int argc, char **argv)
{
    void *maps;
    size_t filesize;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <elf-file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    maps = open_and_map_file(argv[1], &filesize);
    if (!maps) {
        return EXIT_FAILURE;
    }

    process_elf(maps, filesize);
    munmap(maps, filesize);
    return EXIT_SUCCESS;
}
