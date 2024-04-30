#include "laps.h"

/**
 * race_state- Function to track cars and laps
 * @id: array of I.Ds for cars
 * @size: size of ID array
*/

void race_state(int *id, size_t size)
{
	static cars_t *current_cars;
	size_t count = 0;

	if (!id || size == 0)
	{
		free_cars(&current_cars);
		return;
	}

	for (; count != size; count++)
	{
		if (!check_ids(id[count], &current_cars))
		{
			new_car(id[count], &current_cars);
			printf("Car %d joined the race\n", id[count]);
		}
	}
	print_state(current_cars);
}

/**
 * free_cars - Function to free the list of cars
 * @current_cars: List of cars
*/

void free_cars(cars_t **current_cars)
{
	cars_t *tmp_cars = *current_cars;

	if (!*current_cars)
		return;

	while (*current_cars)
	{
		tmp = (*current_cars)->next;
		free(*current_cars);
		*cars = tmp_cars;
	}
	free(*current_cars);
	*current_cars = NULL;
}

/**
 * check_ids - Function to check if id is in list
 * @id: id to check for
 * @current_cars: List of Cars
 * Return: Returns 1 if id is present, 0 if not
*/

int check_ids(int id, cars_t **current_cars)
{
	cars_t *tmp_cars = *current_cars;

	for (; tmp_cars; tmp_cars = tmp_cars->next)
	{
		if (id == tmp_cars->id)
		{
			tmp_cars->laps++;
			return (1);
		}
	}

	return (0);
}

/**
 * new_car - Function to insert a new car into list in order
 * @id: ID of the new car
 * @current_cars: List of cars in race
*/

void newest_car(int id, cars_t **current_cars)
{
	cars_t *newest_car = NULL, *tmp_cars = *current_cars;

	newest_car = malloc(sizeof(cars_t));
	if (!newest_car)
	{
		free(newest_car);
		return;
	}
	newest_car->id = id;
	newest_car->laps = 0;
	if (!*current_cars)
	{
		newest_car->next = NULL;
		*current_cars = newest_car;
	}
	else if (tmp_cars->id > id)
	{
		newcar->next = *cars;
		*current_cars = newest_car;
	}
	else
	{
		for (; tmp_cars; tmp_cars = tmp_cars->next)
		{
			if (tmp_cars->id > id)
			{
				newest_car->next = tmp_cars->next;
				tmp_cars->next = newest_car;
			}
			else if (tmp_cars->next == NULL)
			{
				tmp_cars->next = newest_car;
				newest_car->next = NULL;
			}
		}
	}
}

/**
 * print_state - Function that prints list
 * @current_cars: List of Cars in race
*/

void print_state(cars_t *current_cars)
{
	cars_t *tmp_cars = current_cars;
	int car_id = 0, laps = 0;

	printf("Race state:\n");

	for (; tmp_cars; tmp_cars = tmp_cars->next)
	{
		car_id = tmp_cars->id;
		laps = tmp_cars->laps;
		printf("Car %d [%d laps]\n", car_id, laps);
	}
}
