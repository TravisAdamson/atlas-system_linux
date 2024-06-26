#include <limits.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <dirent.h>
#include "hls.h"

#define PATH_MAX 4096

static char PATH_BUFF[PATH_MAX];
static char PERMS_ALPHAMAP[3] = { 'r', 'w', 'x' };
static char FTYPE_ALPHAMAP[16] = {
	'?', 'p', 'c', '?',
	'd', '?', 'b', '?',
	'-', '?', 'l', '?',
	's', '?', '?', '?'
};

/**
 * dirent_type_name - Translate the type to usable data
 * @d_type: The given type
 * Return: Translated type as a usable value
*/

const char *dirent_type_name(unsigned char d_type)
{
	switch (d_type)
	{
	case DT_BLK:
		return ("block_device");
	case DT_CHR:
		return ("character_device");
	case DT_DIR:
		return ("directory");
	case DT_FIFO:
		return ("named_pipe");
	case DT_LNK:
		return ("symbolic_link");
	case DT_REG:
		return ("file");
	case DT_SOCK:
		return ("socket");
	default:
		return ("unknown");
	}
}

/**
 * path_join - Combine dir_path and the entry_name
 * @dirpath: the path for the directory
 * @entry_name: The name for the given entry
 * Return: A combined string value
*/

const char *path_join(const char *dirpath, const char *entry_name)
{
	snprintf(PATH_BUFF, PATH_MAX, "%s/%s", dirpath, entry_name);
	return (PATH_BUFF);
}

/**
 * mode_to_str - Translate the mode to a usable string value
 * @buf: Formatted string translation of the mode
 * @mode: Mode to translate
 * Return: Always 0
*/

int mode_to_str(char *buf, mode_t mode)
{
	mode_t pmask, i;

	/* maps the file-type bits to a value 0-15 */
	*buf++ = FTYPE_ALPHAMAP[(mode & S_IFMT) >> 12];

	/* masks read permissions of owner first */
	pmask = S_IRUSR;

	/**
	 * check each permission bit and map to alpha code
	 * owner:  i = 0-2 (rwx)
	 * group:  i = 3-5 (rwx)
	 * others: i = 6-8 (rwx)
	 */
	for (i = 0; i < 9; ++i, pmask >>= 1)
		*buf++ = (mode & pmask) ? PERMS_ALPHAMAP[i % 3] : '-';

	*buf = '\0';

	return (0);
}

/**
 * dir_long_init - Initialize the dir_long_t struct for -l option
 * @long_data: struct to load the long listing values for printing
 * @entry_name: The name of the current entry
 * @stat_buff: The struct with the stat information to use
 * Return: 0 for success, -1 for failure
*/

int dir_long_init(dir_long_t *long_data,
				  const char *entry_name,
				  stat_t *stat_buff)
{
	struct passwd *pwd = NULL;
	struct group *group = NULL;

	mode_to_str(long_data->mode, stat_buff->st_mode);
	long_data->nlinks = stat_buff->st_nlink;

	pwd = getpwuid(stat_buff->st_uid);
	group = getgrgid(stat_buff->st_gid);

	if (!pwd || !group)
		return (-1);

	long_data->user = pwd->pw_name;
	long_data->group = group->gr_name;
	long_data->size = stat_buff->st_size;
	long_data->mod = ctime(&(stat_buff->st_mtime));
	long_data->name = entry_name;

	return (0);
}

/**
 * dir_long_print - Print the longlist version
 * @long_data: struct holding dir_info data
*/

void dir_long_print(dir_long_t *long_data)
{
	printf("%s %lu %s %s %-4lu %.*s %s\n",
		   long_data->mode,
		   long_data->nlinks,
		   long_data->user,
		   long_data->group,
		   long_data->size,
		   (int)strlen(long_data->mod) - 1,
		   long_data->mod,
		   long_data->name
	);
}
