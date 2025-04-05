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
			printf("We are process y (pid: %d, ppid: %d, id1: %d, id2: %d)\n", getpid(), getppid(), id1, id2);
		else
			printf("We are process x (pid: %d, ppid: %d, id1: %d, id2: %d)\n", getpid(), getppid(), id1, id2);
	else
		if (id2 == 0)
			printf("We are process z (pid: %d, ppid: %d, id1: %d, id2: %d)\n", getpid(), getppid(), id1, id2);
		else
			printf("We are parent process (pid: %d, id1: %d, id2: %d) \n", getpid(), id1, id2);
	//In order to wait() only for child processes to finish, we can check if the process ia actually a child
	while (wait(NULL) != -1 || errno != ECHILD)
		printf("Waited for a child to finish \n");
	return 0;
}
