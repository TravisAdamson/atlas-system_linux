#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

/**
 * main - Sockets server
 * Return: Success or Failure
*/
int main(void)
{
	int socket_fd, connect;
	char buffer[1024];
	struct sockaddr_in s_address;
	socklen_t addrlen = sizeof(s_address);

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd == -1)
		perror("socket failed"), exit(EXIT_FAILURE);

	s_address.sin_family = AF_INET;
	s_address.sin_port = htons(12345);
	s_address.sin_addr.s_addr = INADDR_ANY;

	if (bind(socket_fd, (struct sockaddr *)&s_address, sizeof(s_address)) < 0)
		perror("bind failed"), exit(EXIT_FAILURE);

	printf("Server listening on port 12345\n");
	if (listen(socket_fd, 5) < 0)
		perror("listen failed"), exit(EXIT_FAILURE);

	connect = accept(socket_fd, (struct sockaddr *)&s_address, &addrlen);
	if (connect < 0)
		perror("accept failed"), exit(EXIT_FAILURE);
	printf("Client connected: %s\n", inet_ntoa(s_address.sin_addr));

	read(connect, buffer, 1024 - 1);
	printf("Message received: ");
	printf("\"%s\"\n", buffer);
	close(connect), close(socket_fd);
	return (0);
}
