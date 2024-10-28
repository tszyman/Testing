#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/wait.h>

/* Simulating the pipe "|" operator */
/* Simulate ping -c 3 google.com | grep rtt */
/* To do that, we need to:
	1. Create a pipe
	2. Create two forks
	3. One child process will perform execlp ping -c 3 google.com
	4. Second child process will perform grep rtt on the outcome of the first one

 */
int main()
{
	int	fd[2];
	int	pid1;
	int	pid2;

	if (pipe(fd) == -1)
		return 1;

	pid1 = fork();	
	if (pid1 < 0)
		return 2;

	if (pid1 == 0)
	{
		//Child process1 (ping	)
		dup2(fd[1],STDOUT_FILENO);		//
		close(fd[0]);					// we dont need read-end
		close(fd[1]);					// we've already duplicated write-end to STDOUT, so we can close fd[1] already
		printf("[child1] Starting ping...\n");
		execlp("ping", "ping", "-c", "3", "google.com", NULL);
	}
	
	pid2 = fork();
	if (pid2 < 0)
		return 3;
	if (pid2 == 0)
	{
		//Child process2 (grep)
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);	
		close(fd[0]);
		printf("[child2] Starting grep...");
		execlp("grep", "grep", "rtt", NULL);
	}

	close(fd[0]);
	close(fd[1]);

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return 0;
}

