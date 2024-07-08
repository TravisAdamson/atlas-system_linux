#include <sys/types.h>
#include <signal.h>

/**
 * pid_exist - checks for given pid
 * @pid: the pid to look for
 * Return: 1 if exists else 0
 */
int pid_exist(pid_t pid)
{
	return (!kill(pid, 0));
}
