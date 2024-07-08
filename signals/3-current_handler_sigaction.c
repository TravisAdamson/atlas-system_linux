#include "signals.h"

/**
 * current_handler_sigaction - Finds current handler
 * Return: pointer to handler, or NULL
*/

void (*current_handler_sigaction(void))(int)
{
	struct sigaction org_handler;

	if (sigaction(SIGINT, NULL, &org_handler) == -1)
		return (NULL);
	return (org_handler.sa_handler);
}
