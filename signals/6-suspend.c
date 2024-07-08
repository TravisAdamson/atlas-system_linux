#include "signals.h"

/**
 * sig_catch - finds pid of process that sent SIGQUIT
 * @sig: signal received
*/

void sig_catch(int sig)
{
	printf("Caught %d\n", sig);
	fflush(stdout);
}

/**
 * main - entry to program
 * @argc: number of arguments. Unused
 * @argv: Array of arguments, Unused
 * Return: 0 on success, -1 on fail
*/

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	set_handler();
	pause();
	printf("Signal received\n");
	return (EXIT_SUCCESS);
}

/**
 * set_handler - sets SIGINT handler, waits for sig
 * Return: 0 on success, -1 on fail
*/

int set_handler(void)
{
	struct sigaction sig_handler;

	sig_handler.sa_handler = sig_catch;
	return (sigaction(SIGINT, &sig_handler, NULL));
}
