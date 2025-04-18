#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/wait.h>

/* waitpid example */

int	main()
{
	int	pid1;
	int	pid2;

	pid1 = fork();
	if (pid1 == -1)
		return 1;
	if (pid1 == 0)
	{
		sleep(4);
		printf("Finished execution (%d)\n", getpid());
		return 0;
	}

	pid2 = fork();
	if (pid2 == -1)
		return 2;
	if (pid2 == 0)
	{
		sleep(1);
		printf("Finished execution (%d)\n", getpid());
		return 0;
	}

	int pid1_res = waitpid(pid1, NULL, 0);
	printf("Waited for %d\n", pid1_res);
	int pid2_res = waitpid(pid2, NULL, 0);
	printf("Waited for %d\n", pid2_res);
	return 0;
}