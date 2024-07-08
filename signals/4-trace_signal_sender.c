#include "signals.h"

/**
 * find_pid - finds pid of process that sent SIGQUIT
 * @sig: signal received
 * @sig_handler: handler struct
 * @context: necessary per protocol
*/

void find_pid(int sig, siginfo_t *sig_handler, void *context)
{
	printf("SIGQUIT sent by %d\n", sig_handler->si_pid);
	fflush(stdout);
	(void)sig;
	(void)context;
}

/**
 * trace_signal_sender - sets a handler for SIGQUIT
 * Return: 0 on success, or -1
*/

int trace_signal_sender(void)
{
	struct sigaction sig_handler;

	sig_handler.sa_flags = SA_SIGINFO;
	sig_handler.sa_sigaction = find_pid;
	return (sigaction(SIGQUIT, &sig_handler, NULL));
}
