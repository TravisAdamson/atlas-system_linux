#include "syscall.h"

void print_params(size_t i, struct user_regs_struct *regs);

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
	size_t i = 0;

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
			ptrace(PTRACE_GETREGS, child, NULL, &regs);
			if (WIFEXITED(status))
			{
				fprintf(stderr, " = ?\n");
				break;
			}
			if (print_check == 0 || print_check % 2 != 0)
			{
				fprintf(stderr, "%s(", SYSNAME);
				for (i = 0; i < SYSPARAM; i++)
				{
					if (SYSTYPE == VOID)
						continue;
					if (SYSTYPE == VARARGS)
						fprintf(stderr, ", ...");
					else
						print_params(i, &regs);
				}
			}
			if (print_check % 2 == 0)
			{
				fprintf(stderr, ") = %#lx\n", (size_t)regs.rax);
			}
			print_check++;
		}
	}
	return (0);
}

void print_params(size_t i, struct user_regs_struct *regs)
{
	switch (i)
	{
		case 0:
			fprintf(stderr, "%#lx", (size_t)regs->rdi);
			return;
		case 1:
			fprintf(stderr, ", %#lx", (size_t)regs->rsi);
			return;
		case 2:
			fprintf(stderr, ", %#lx", (size_t)regs->rdx);
			return;
		case 3:
			fprintf(stderr, ", %#lx", (size_t)regs->r10);
			return;
		case 4:
			fprintf(stderr, ", %#lx", (size_t)regs->r8);
			return;
		case 5:
			fprintf(stderr, ", %#lx", (size_t)regs->r9);
			return;
		default:
			return;
	}
}
