#include "multithreading.h"
#include <stdlib.h>

/**
 * prime_factors - factors a given number into a list containing prime factors
 * @s: string of the number to factor
 * Return: list of prime factors
 **/
list_t *prime_factors(char const *s)
{
	unsigned long num = strtoul(s, NULL, 10);
	unsigned long *temp, prime = 2;
	list_t *prime_list = malloc(sizeof(list_t));

	list_init(prime_list);
	while (prime * prime <= num)
	{
		while (num % prime == 0)
		{
			temp = malloc(sizeof(unsigned long));
			*temp = prime;
			list_add(prime_list, (void *)temp);
			num /= prime;
		}

		prime += 1 + (prime != 2);
	}

	if (num >= 2)
	{
		temp = malloc(sizeof(unsigned long));
		*temp = num;
		list_add(prime_list, (void *)temp);
	}
	return (prime_list);
}
