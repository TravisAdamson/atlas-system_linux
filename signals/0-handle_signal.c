#include "signals.h"

/**
 * sigint_processor - Action to be taken on SIGINT
 * @sig: Incoming signal
*/

void sigint_processor(int sig)
{
	printf("Gotcha! [%d]\n", sig);
	fflush(stdout);
}

/**
 * handle_signal - function for handling SIGINT
 * Return: 0 on success, -1 on failure
*/

int handle_signal(void)
{
	if (signal(SIGINT, sigint_processor) == SIG_ERR)
		return (-1);
	else
		return (0);
}
