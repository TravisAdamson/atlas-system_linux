#include "syscall.h"

/**
 * main - Main function
 * @argc: Number of arguments provided
 * @argv: array of arguments provided
 * @envp: Environment variable
 * Return: returns -1 on fail, or 0 on success
*/

int main(int argc, char **argv, char **envp)
{
	pid_t child;
	int status, print_check = 0;
	struct user_regs_struct regs;

	if (argc < 2)
	{
		fprintf(stderr, "Unsupported number of Arguments\n");
		return (-1);
	}
	child = fork();
	if (child == 0)
	{
		ptrace(PTRACE_TRACEME, child, NULL, NULL);
		execve(argv[1], &argv[1], envp);
	}
	else
	{
		while (1)
		{
			ptrace(PT_SYSCALL, child, NULL, NULL);
			wait(&status);
			if (WIFEXITED(status))
				break;
			ptrace(PTRACE_GETREGS, child, NULL, &regs);

			if (print_check == 0 || print_check % 2 != 0)
			{
				if (regs.orig_rax !=1)
					fprintf(stderr, "%s\n", SYSNAME);
				else
					fprintf(stderr, "%s", SYSNAME);
			}
			if (print_check % 2 == 0 && regs.orig_rax == 1)
				fprintf(stderr, "\n");
			print_check++;
		}
	}
	return (0);
}
