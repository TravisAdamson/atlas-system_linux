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

/**
 * main - Socket Client
 * @argc: number of arguments
 * @argv: array of args
 * Return: 0 on success
*/
int main(int argc, const char **argv)
{
	int client_fd;
	struct sockaddr_in server_add, *address;
	struct hostent *host;
	struct addrinfo a_struct = {0}, *addrs, *tmp = NULL;
	char ip[16] = {0};

	if (argc < 3)
		printf("Usage: %s <host> <port>\n", argv[0]), exit(EXIT_FAILURE);

	host = gethostbyname(argv[1]);
	if (host == NULL)
		perror("host not found"), exit(EXIT_FAILURE);
	a_struct.ai_family = AF_INET;
	a_struct.ai_socktype = SOCK_STREAM;
	a_struct.ai_protocol = IPPROTO_TCP;
	if (getaddrinfo(argv[1], argv[2], &a_struct, &addrs) != 0)
		perror("Failed to get address info"), exit(EXIT_FAILURE);
	for (tmp = addrs; tmp != NULL; tmp = tmp->ai_next)
	{
		address = (struct sockaddr_in *)tmp->ai_addr;
		client_fd = socket(a_struct.ai_family, a_struct.ai_socktype, 0);
		if (client_fd == -1)
			perror("socket failed"), exit(EXIT_FAILURE);
		server_add.sin_family = AF_INET;
		server_add.sin_port = htons(atoi(argv[2]));
		inet_ntop(AF_INET, &(address->sin_addr), ip, INET_ADDRSTRLEN);
		server_add.sin_addr.s_addr = inet_addr(ip);
		if (connect(client_fd, (struct sockaddr *) &server_add,
					sizeof(struct sockaddr_in)) < 0)
			perror("Failed to Connect\n"), exit(EXIT_FAILURE);
		printf("Connected to %s:%s\n", argv[1], argv[2]);
		close(client_fd);
		break;
	}
	freeaddrinfo(addrs);
	return (0);
}
