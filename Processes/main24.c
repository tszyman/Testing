#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/wait.h>

/* Multiple Pipes */
/* We want to create:
	- two child processes (thee in total)
	- three pipes passing the values between those processes and adding 5 to x
					Parent process
				pipe0/			\pipe2
			Child1 (x+5) -pipe1-> Child2 (x+5) 
			pipe0: fd[0][0] = read():	Child1 (x)
			pipe0: fd[0][1] = write():	Parent (x)
			pipe1: fd[1][0] = read():	Child2 (x+5)
			pipe1: fd[1][1] = write():	Child1 (x+5)
			pipe2: fd[2][0] = read():	Parent (x+5+5)
			pipe2: fd[2][1] = write()	Child2 (x+5+5)
*/

int	main()
{
	int	pid1;
	int	pid2;
	int	fd[3][2];
	int	x;
	int	i;

	i = 0;
	while (i < 3)
	{
		if(pipe(fd[i]) < 0)
			return 1;
		i++;
	}
	pid1 = fork();
	if (pid1 == -1)
		return 2;
	if (pid1 == 0)
	{
		//Child1
		int x;
		close(fd[0][1]);
		close(fd[1][0]);
		close(fd[2][0]);
		close(fd[2][1]);
		if (read(fd[0][0], &x, sizeof(int)) < 0)
			return 5;
		x += 5;
		if (write(fd[1][1], &x, sizeof(int)) < 0)
			return 6;
		close(fd[0][0]);
		close(fd[1][1]);
		return 0;
	}

	pid2 = fork();
	if (pid2 == -1)
		return 3;
	if (pid2 == 0)
	{
		//Child2
		int x;
		close(fd[0][0]);
		close(fd[0][1]);
		close(fd[1][1]);
		close(fd[2][0]);
		if (read(fd[1][0], &x, sizeof(int)) < 0)
			return 7;
		x += 5;
		if (write(fd[2][1], &x, sizeof(int)) < 0)
			return 8;
		close(fd[1][0]);
		close(fd[2][1]);
		return 0;
	}

	//Parent process
	close(fd[0][0]);	//parent will not need to read on pipe0
	close(fd[1][0]);	//parent will not need to read on pipe1
	close(fd[1][1]);	//parent will not need to write on pipe1
	close(fd[2][1]);	//parent will not need to write on pipe2
	printf("Please enter some value: ");
	scanf("%d", &x);
	if (write(fd[0][1], &x, sizeof(int)) < 1)
		return 4;
	if (read(fd[2][0], &x, sizeof(int)) < 0)
		return 9;
	printf("Final result is %d\n", x);
	close(fd[0][1]);	//parent finished writing on pipe0, so can be closed
	close(fd[2][0]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

	return 0;
}