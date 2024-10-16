#ifndef SOCKETS_H
#define SOCKETS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#ifndef __USE_XOPEN2K
#define __USE_XOPEN2K
#endif
#include <netdb.h>

/*MACROS*/
#define STAT_201 "HTTP/1.1 201 Created\r\n"
#define STAT_404 "HTTP/1.1 404 Not Found\r\n\r\n"
#define STAT_411 "HTTP/1.1 411 Length Required\r\n\r\n"
#define STAT_422 "HTTP/1.1 422 Unprocessable Entity\r\n\r\n"

/*Structs*/
/**
 * todo - list of to do tasks
 * @id: id number of task
 * @title: name of task
 * @description: description of task
 * @next: pointer to next node in list
 */
typedef struct todo
{
    size_t id;
    char *title;
    char *description;
    struct todo *next;
} todo_t;

/*Prototypes*/
void process_req(char *request, int fd);
void query_parser(char *query);
void body_parser(char *query);
void head_parser(char *query, int fd);
void task_parser(char *query, int fd);
void add_todo(char *desc, char *title, int fd);

#endif
