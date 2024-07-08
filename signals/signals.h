#ifndef __SIGNALS_H_
#define __SIGNALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

int handle_signal(void);
void (*current_handler_signal(void))(int);

#endif
