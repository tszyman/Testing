#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/wait.h>

/* What does fork() actually return? */
/* 
	Inside parent process - child process id - it's going to be different than getpid()
	Inside child process - 0 - it's going to be different than getpid()
 */

int	main()
{
	int	id;
	int res;

	id = fork();
	if (id == 0)
		sleep(1);
	printf("Returned by fork: %d, Current ID: %d, Parent ID: %d\n", id, getpid(), getppid());
	res = wait(NULL);
	if (res == -1)
		printf("No children to wait for\n");
	else
		printf("%d finished execution\n", res);

	return 0;
}