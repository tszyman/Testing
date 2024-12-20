#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <time.h>
#include <sys/wait.h>
#include <signal.h>

/* Short introduction to signals in C */

int main()
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return 1;
	if (pid == 0)
	{
		while (1)
		{
			printf("Some text goes here\n");
			usleep(50000);
		}
	}
	else
	{
		sleep(1);
		kill(pid, SIGKILL);
		wait(NULL);
	}
	return 0;
}
