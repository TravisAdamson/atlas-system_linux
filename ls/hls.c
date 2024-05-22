#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "hls.h"

#define PRINT_TRUE(entry, flag_a) \
        ((entry)->d_name[0] != '.' || (flag_a))

static int get_flags(char **argv, const int argc, dir_info_t *comm_line)
{
    int i = 0, error_flag = 0;

    if (!argv || !comm_line)
        return (-1);
    
    for (; i != argc - 1; i++)
    {
        if (argv[i][0] == '-')
        {
            if (argv[i][1] != '-')
            {
                if (argv[i][1] == '1')
                    comm_line->flag_1 = 1;
                if (argv[i][1] == 'a')
                    comm_line->flag_a = 1;
                if (argv[i][1] == 'A')
                    comm_line->flag_A = 1;
                if (argv[i][1] == 'l')
                    comm_line->flag_l = 1;
            }
        }
    }

    return (0);
}

static int print_data(dir_info_t *comm_line)
{
    struct stat stat_buff;
    dir_long_t long_data;

    const char *entry_name = NULL;
    const char *entry_path = NULL;

    if (!PRINT_TRUE(comm_line->current_entry, comm_line->flag_a))
        return (0);
    
    if (comm_line->flag_l)
    {
        entry_name = comm_line->current_entry->d_name;
        entry_path = path_join(comm_line->path, entry_name);

        if (lstat(entry_path, &stat_buff) == -1)
            return (-1);
        
        dir_long_init(&long_data, entry_name, &stat_buff);
        dir_long_print(&long_data);
    }
    else
    {
        printf("%s ", comm_line->current_entry->d_name);
        return(0);
    }
}

int main(const int argc, char **argv)
{
    dir_info_t comm_line;
    const char *dir_path = NULL;

    dir_path = argv[1];

    if (argc > 1)
    {
        if (get_flags(argv, argc, &comm_line) == -1)
            return (EXIT_FAILURE);
    }

    if (dir_info_init(&comm_line, dir_path) == -1)
    {
        fprintf(stderr,
                "Failure opening directory '%s'\n",
                dir_path);
        return (EXIT_FAILURE);
    }

    if (dir_info_each(&comm_line, print_data) == -1)
    {
        fprintf(stderr,
                "Error parsing directory '%s'\n",
                dir_path);
        return (EXIT_FAILURE);
    }
    
    dir_info_clear(&comm_line);

    return (0);
}