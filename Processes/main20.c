#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <signal.h>
#include <bits/sigaction.h>
#include <asm-generic/signal-defs.h>

/* Communicating between processes using signals */

int main()
{
	int	pid;
	int	x;
	struct sigaction sa;

	sa.sa_flags = SA_RESTART;
	
	pid = fork();
	if (pid == -1)
		return 1;
	if (pid == 0)
	{
		// Child process
		sleep(5);
		kill(getppid(), SIGUSR1);
	}
	else
	{
		// Parent process
		printf("What is the result 3 x 5: ");
		scanf("%d", &x);
		if (x == 15)
			printf("Right!");
		else
			printf("Wrong!");
	}
	return 0;
}
