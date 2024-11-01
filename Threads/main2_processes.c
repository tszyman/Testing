#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/wait.h>

int	main()
{
	int	pid;
	int	x;

	pid = fork();
	x = 2;
	if (pid == -1)
		return 1;
	if (pid == 0)
		x++;
	sleep(2);
	printf("Value of x: %d\n", x);
	if (pid != 0)
		wait(NULL);
	return 0;
}