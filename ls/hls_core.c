#include <dirent.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include "hls.h"

int dir_info_init(dir_info_t *comm_line, const char *path) 
{
    DIR *dir = NULL;

    if (!comm_line || !path)
        return (-1);
    
    dir = opendir(path);

    if (!dir)
        return (-1);
    
    comm_line->directory = dir;
    comm_line->path = path;
    comm_line->current_entry = NULL;
    comm_line->stop = 0;
    comm_line->flag_1 = 0;
    comm_line->flag_a = 0;
    comm_line->flag_A = 0;
    comm_line->flag_l = 0;

    return (0);
}

struct dirent *dir_info_next(dir_info_t *comm_line)
{
    struct dirent *next_entry = NULL;

    if (comm_line->stop)
        return (NULL);
    
    next_entry = readdir(comm_line->directory);

    if (next_entry)
        comm_line->current_entry = next_entry;
    else
    {
        comm_line->stop = 1;
        comm_line->current_entry = NULL;
    }

    return (next_entry);
}

int dir_info_each(dir_info_t *comm_line, dirent_instruct_t instruct)
{
    int count_entries = 0;

    if (!comm_line || !instruct)
        return (-1);
    
    while (dir_info_next(comm_line))
    {
        if (instruct(comm_line) == -1)
        {
            fprintf(stderr,
                    "Failer opening entry: '%s'\n",
                    comm_line->current_entry->d_name);
        }

        ++count_entries;
    }

    return (count_entries);
}

void dir_info_clear(dir_info_t *comm_line)
{
    if (!comm_line)
        return;
    
    closedir(comm_line->directory);
    memset(comm_line, 0, sizeof(*comm_line));
}