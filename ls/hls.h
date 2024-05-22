#ifndef _HSL_H_
#define _HSL_H_


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <errno.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

/**
 * struct dir_info - The structure holding the details of the command
 * @directory: The DIR representing this instance
 * @path: Location to the directory
 * @currrent_entry: Pointer to current struct dirent
 * @stop: Flag to indicate the end of entry
 * @flag_1: Flag indicating the -1 option
 * @flag_a: Flag indicating the -a option
 * @flag_A: Flag indicating the -A option
 * @flag_l: flag indicating the -l option
*/

typedef struct dir_info
{
	DIR *directory;
	const char *path;
	struct dirent *current_entry;
	int stop;
	int flag_1;
	int flag_a;
	int flag_A;
	int flag_l;
} dir_info_t;

typedef int (*dirent_instruct_t)(dir_info_t *comm_line);

int dir_info_init(dir_info_t *comm_line, const char *path);

struct dirent *dir_info_next(dir_info_t *comm_line);

int dir_info_each(dir_info_t *comm_line, dirent_instruct_t instruct);

void dir_info_clear(dir_info_t *comm_line);

/**
 * dir_long - Formating for the long listing option
 * @mode: Permissions data
 * @nlinks: The nlink object
 * @user: The user ID
 * @group: The group ID
 * @size: The size of the entry
 * @mod: Modified date
 * @name: The name of the directory
*/

typedef struct dir_long
{
	char mode[16];
	nlink_t nlinks;
	const char *user;
	const char *group;
	off_t size;
	const char *mod;
	const char *name;
} dir_long_t;

const char *dirent_type_name(unsigned char d_type);

const char *path_join(const char *dir_path, const char *dir_name);
int mode_to_str(char *buf, mode_t mode);

int dir_long_init(dir_long_t *long_data,
				  const char *dir_name,
				  struct stat *stat_buff);

void dir_long_print(dir_long_t *long_data);

#endif
