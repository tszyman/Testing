#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/wait.h>
#include <signal.h>

/* Stopping and continuing the execution of a process (using SIGSTOP and SIGCONT) */

int main()
{
	int	pid;
	int	t;

	pid = fork();
	if (pid == -1)
		return 1;
	if (pid == 0)
	{
		while (1)
		{
			printf("Some output.\n");
			usleep(50000);
		}
	}
	else
	{
		kill(pid, SIGSTOP);
		do
		{
			printf("Time in second for execution: ");
			scanf("%d", &t);
			if (t > 0)
			{
				kill(pid, SIGCONT);
				sleep(t);
				kill(pid, SIGSTOP);
			}
		} while (t > 0);
		kill(pid, SIGKILL);
		wait(NULL);
	}

	return 0;
}

