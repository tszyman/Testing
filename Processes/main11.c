#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/wait.h>

/* Executing commands in C */

int main()
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return 1;
	if (pid == 0)
	{
		// Child process
		execlp("ping", "ping", "-c", "3", "google.com", NULL);
	}
	else
	{
		// Parent process
		wait(NULL);
		printf("Success!\n");
		printf("Add some postprocessing here.\n");
	}
	return 0;
}
