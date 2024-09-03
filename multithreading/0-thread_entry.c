#include "multithreading.h"
#include <pthread.h>
#include <stdio.h>

/**
 * thread_entry - entry point to a created thread
 * @arg: address of a string
 * Return: None
 **/

void *thread_entry(void *arg)
{
	if (arg)
		puts((char *)arg);
	pthread_exit(NULL);
}
