#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/* Process IDs in C */

int main()
{
	int	id;
	int res;

	id = fork();
	if (id == 0)
		sleep(1);
	if (id == 0)
	{
		printf("This is child id:\n");
		printf("Current ID: %d, Parent ID: %d, Fork ID: %d\n", getpid(), getppid(), id);
	}
	else
	{
		printf("This is main id:\n");
		printf("Current ID: %d, Parent ID: %d, Fork ID: %d\n", getpid(), getppid(), id);
	}
	res = wait(NULL);
	if (res == -1)
		printf("No children to wait for! \n");
	else
		printf("%d finished execution\n", res);
	return 0;
}

