#include "signals.h"

/**
 * main - Describes the signal received
 * @argc: Number of arguements
 * @argv: Array of arguements
 * Return: Success or Failure
*/

int main(int argc, char **argv)
{
	int sig_arg = atoi(argv[1]);

	if (argc != 2)
	{
		printf("Usage %s <signum>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	if (strsignal(sig_arg))
		printf("%d: %s\n", sig_arg, strsignal(sig_arg));
	else
		printf("%d: %s %d\n", sig_arg, strsignal(sig_arg), sig_arg);
	return (EXIT_SUCCESS);
}
