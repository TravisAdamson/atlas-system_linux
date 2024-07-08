#include "signals.h"

/**
 * main - Describes the signal
 * @argc: Number of arguements
 * @argv: Array of arguements
 * Return: Success or Failure
*/

int main(int argc, char **argv)
{
	int sig_flag;

	if (argc != 2)
	{
		printf("Usage: %s <pid>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	sig_flag = kill(atoi(argv[1]), 2);
	if (sig_flag != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
