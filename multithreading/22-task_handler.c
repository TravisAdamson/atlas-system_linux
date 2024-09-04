#include "multithreading.h"

/**
 * exec_task - executes the specified task and returns the result
 * @task: given task
 * Return: task results
 */
void *exec_task(task_t *ind_task)
{
	void *result;

	result = ind_task->entry(ind_task->param);
	pthread_mutex_lock(&ind_task->lock);
	ind_task->result = result;
	pthread_mutex_unlock(&ind_task->lock);
	return (result);
}

/**
 * get_status - gets a task status staying thread-safe
 * @task: task
 * Return: task status
 */
task_status_t get_status(task_t *ind_task)
{
	task_status_t stat;

	pthread_mutex_lock(&ind_task->lock);
	stat = ind_task->status;
	pthread_mutex_unlock(&ind_task->lock);
	return (stat);
}

/**
 * set_status - sets a task status staying thread-safe
 * @task: task
 * @status: new status
 */
void set_status(task_t *ind_task, task_status_t stat)
{
	pthread_mutex_lock(&ind_task->lock);
	ind_task->status = stat;
	pthread_mutex_unlock(&ind_task->lock);
}
