#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

/* Waiting for processes to finish using wait() function */

int main()
{
	int	id;	
	int	n;
	int	i;
	int status;

	status = 0;
	id = fork();
	if (id == 0)
	{
		n = 1;
	}
	else
	{
		n = 6;
	}
	if (id != 0 )
		wait(&status);
	i = n;
	while (i < n + 5)
	{
		printf("%d ", i);
		fflush(stdout);
		i++;
	}
	if (id != 0)
		printf("\n");
	return 0;
}
