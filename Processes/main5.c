#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <errno.h>

/* Calling fork() multiple times */

int main()
{
	int	id1;
	int	id2;

	id1 = fork();
	id2 = fork();
	if (id1 == 0)
		if (id2 == 0)
			printf("We are process y\n");
		else
			printf("We are process x\n");
	else
		if (id2 == 0)
			printf("We are process z \n");
		else
			printf("We are parent process \n");
	//In order to wait() only for child processes to finish, we can check if the process ia actually a child
	while (wait(NULL) != -1 || errno != ECHILD)
		printf("Waited for a child to finish \n");
	return 0;
}
