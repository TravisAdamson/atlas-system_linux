#ifndef _GETLINE_H_
#define _GETLINE_H_

#define READ_SIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * struct file_buff- node for holding buffer info
 * @file_desc: file descriptor
 * @buffer: holds text that has been read
 * @num_bytes: Size of buffer
 * @position: position of cursor in buffer
 * @flags: flag for newline character
 * @next: points to next nore or NULL
*/

typedef struct file_buff
{
	int file_desc;
	char *buffer;
	ssize_t num_bytes;
	size_t position;
	size_t flags;
	struct file_buff *next;
} file_buff_t;

char *_getline(const int fd);
file_buff_t *node_locate(file_buff_t **list, int fd);
file_buff_t *adding_node(file_buff_t **list, int fd);
char *reading(int fd);
char *next_line(file_buff_t *file);
#endif