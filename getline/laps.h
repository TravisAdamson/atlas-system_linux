#ifndef _LAPS_H_
#define _LAPS_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * struct cars - Singly linked list of cars
 * @id: id of the car
 * @laps: Number of laps completed
 * @next: points to next node
*/

typedef struct cars
{
	int id;
	int laps;
	struct cars *next;
} cars_t;

void race_state(int *id, size_t size);
int check_ids(int id, cars_t **current_cars);
void free_cars(cars_t **current_cars);
void newest_car(int id, cars_t **current_cars);
void print_state(cars_t *current_cars);

#endif
