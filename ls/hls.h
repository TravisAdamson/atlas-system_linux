#ifndef _HSL_H_
#define _HSL_H_

#define READ_SIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

/**
 * struct list_dir - List of the relevant directories
 * @name: name of the directory
 * @next: next directory in list
 * @prev: previous directory in list
*/

typedef struct list_dir
{
    char *name;
    struct list_dir *next;
    struct list_dir *prev;
} list_dir_t;

/**
 * struct list_file - list of the relevant files
 * @name: name of the file
 * @next: next file in the list
 * @prev: previous file in the list
*/

typedef struct list_file
{
    char *name;
    struct list_file *next;
    struct list_file *prev;
} list_file_t;

/**
 * struct comm_info - The structure holding the details of the command
 * @my_argc: Nmber of arguments after the executable
 * @dir_c: Number of directories to look at
 * @dir_l: list of the directories to be examined
 * @file_c: Number of files to be shown
 * @file_l: list of files
 * @flags: Optional flags to be included
*/

typedef struct comm_info
{
    int my_argc;
    int dir_c;
    list_dir_t *list_dir;
    int file_c;
    list_file_t *list_file;
    int flags;
} comm_info_t;

typedef struct comm_ordered
{
    char *name;
    int is_dir;
    mode_t mode;
    nlink_t links;
    uid_t owner_id;
    gid_t owner_gp;
    off_t size;
    time_t mtime;
    struct comm_ordered *next;
    struct comm_ordered *prev;
} comm_o;

#endif