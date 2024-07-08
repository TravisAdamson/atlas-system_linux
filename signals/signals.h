#ifndef __SIGNALS_H_
#define __SIGNALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

int handle_signal(void);
void (*current_handler_signal(void))(int);
int handle_sigaction(void);
void sigint_handler(int sig);
void (*current_handler_sigaction(void))(int);
int trace_signal_sender(void);
void find_pid(int sig, siginfo_t *sig_handler, void *context);

int set_handler(void);
void sig_catch(int sig);

#endif
