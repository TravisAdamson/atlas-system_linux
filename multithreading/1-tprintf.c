#include "multithreading.h"
#include <stdio.h>
#include <pthread.h>

/**
 * tprintf - printf used to print a given formated string
 * @format: formatted string to print
 * Return: number of characters printed
 **/

int tprintf(char const *format, ...)
{
	pthread_t self = pthread_self();

	printf("[%lu] %s", self, format);
	return (0);
}
