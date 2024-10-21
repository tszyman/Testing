#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <signal.h>
#include <bits/sigaction.h>
#include <asm-generic/signal-defs.h>
#include <sys/wait.h>

/* Communicating between processes using signals */
int	x = 0;

void	handle_sigusr1()
{
	if (x == 0)
		printf("\n[HINT] Remember that multiplication is repetitive addition.\n");
}

int	main()
{
	int	pid;
	struct sigaction sa = { 0 };

	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &handle_sigusr1;
	sigaction(SIGUSR1, &sa, NULL);
	
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
			printf("Right!\n");
		else
			printf("Wrong!\n");
	}
	wait(NULL);
	return 0;
}
