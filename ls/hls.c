#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "hls.h"

#define PATH_MAX 4096
#define PRINT_TRUE(entry, flag_a) \
		((entry)->d_name[0] != '.' || (flag_a))

/**
 * get_flags - set flags based on given option
 * @argv: The arguments from the command line
 * @argc: The number of arguments given
 * @comm_line: struct holding dir_info data
 * @dir_path: The path for the current directory
 * Return: 0 for success, -1 for failure
*/

static int get_flags(char **argv,
					 const int argc,
					 dir_info_t *comm_line,
					 char *dir_path)
{
	int i = 0;

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
		else
		{
			dir_path = argv[i];
		}
	}

	if (dir_path == NULL)
	{
		dir_path = ".";
	}

	return (0);
}

/**
 * print_data - Print the resulting ls data
 * @comm_line: struct holding dir_info data
 * Return: 0 for success, -1 for failure
*/

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
		return (0);
	}
	else
	{
		printf("%s ", comm_line->current_entry->d_name);
		return (0);
	};
}

/**
 * main - Process the hls command start to finish
 * @argc: The number of given arguments
 * @argv: The array holding the given arguments
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure
*/

int main(const int argc, char **argv)
{
	dir_info_t comm_line;
	char *dir_path = NULL;

	if (argc > 1)
	{
		if (get_flags(argv, argc, &comm_line, dir_path) == -1)
			return (EXIT_FAILURE);
	}
	else
	{
		dir_path = ".";
	}

	if (dir_info_init(&comm_line, dir_path) == -1)
	{
		fprintf(stderr,
				"%s: cannot open directory %s: Permission denied\n",
				argv[0], argv[1]
		);
		return (EXIT_FAILURE);
	}

	if (dir_info_each(&comm_line, print_data) == -1)
	{
		fprintf(stderr,
				"%s: cannot access %s: No such file or directory\n",
				argv[0], argv[1]
		);
		return (EXIT_FAILURE);
	}

	dir_info_clear(&comm_line);

	return (0);
}
