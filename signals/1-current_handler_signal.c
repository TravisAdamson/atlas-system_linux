#include "signals.h"

/**
 * current_handler_signal - gets the current handler of SIGINT
 * Return: pointer to handler or NULL if none
*/

void (*current_handler_signal(void))(int)
{
	__sighandler_t old_handler = signal(SIGINT, SIG_DFL);

	if (old_handler == SIG_ERR)
		return (NULL);
	return (signal(SIGINT, old_handler) == SIG_ERR ? NULL : old_handler);
}
