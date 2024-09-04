#include "multithreading.h"
#include "22-task_handler.c"
#include <stdlib.h>


__attribute__((constructor)) void tasks_mutex_init(void)
{
	pthread_mutex_init(&tasks_mutex, NULL);
}

__attribute__((destructor)) void tasks_mutex_destroy(void)
{
	pthread_mutex_destroy(&tasks_mutex);
}


/**
 * create_task - creates task structure and returns a pointer
 * @entry: pointer to the first function of the task
 * @param: value to give to the first function
 * Return: pointer to the created task structure
 **/

task_t *create_task(task_entry_t entry, void *param)
{
	task_t *ind_task = malloc(sizeof(task_t));
	static unsigned int id;

	if (ind_task)
	{	ind_task->entry = entry;
		ind_task->param = param;
		ind_task->lock = tasks_mutex;
		ind_task->status = PENDING;
		ind_task->result = NULL;
		ind_task->id = id++;
	}

	return (ind_task);
}

/**
 * destroy_task - destroys a task
 * @task: task to destroy
 **/
void destroy_task(task_t *task)
{
	if (task)
	{
		list_destroy(task->result, free);
		free(task->result);
		free(task);
	}
}

/**
 * exec_tasks - executes a list of tasks
 * @tasks: NULL-terminated list of tasks
 * Return: None
 **/
void *exec_tasks(list_t const *tasks)
{
	int pend_task = 1, task_id;
	node_t *this_node;

	if (tasks == NULL)
		pthread_exit(NULL);

	while (pend_task)
		for (pend_task = 0, this_node = tasks->head; this_node; this_node = this_node->next)
			if (get_status(this_node->content) == PENDING)
			{
				pend_task = 1;
				task_id = ((task_t *)this_node->content)->id;
				set_status(this_node->content, STARTED);
				tprintf("[%02d] Started\n", task_id);
				if (exec_task(this_node->content))
				{
					set_status(this_node->content, SUCCESS);
					tprintf("[%02d] Success\n", task_id);
				}
				else
				{
					set_status(this_node->content, FAILURE);
					tprintf("[%02d] Failure\n", task_id);
				}
			}

	return;
}
