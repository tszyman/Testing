#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

/* Sending an array through pipe */
/* 2 processes
	1) Child process should generate random numbers and send them to the parent (child precess sends, parent process reads)
	2) Parent is going to sum all the numbers and print the result
*/

int	main()
{
	int	pid;
	int fd[2];

	if (pipe(fd) == -1)
		return 2;
	pid = fork();
	if (pid == -1)
		return 1;

	if (pid == 0)
	{
		int	n;
		int	i;
		int	arr[10];

		//Child process
		close(fd[0]);						// close reading from pipe (child only writes to pipe)
		srand(time(NULL));
		n = rand() % 10 + 1;
		i = 0;
		printf("[child]Generated array of: ");
		while (i < n)
		{
			arr[i] = rand() % 11;
			printf("%d ", arr[i]);
			i++;
		}
		printf("\n");
		printf("[child]Sending n = %d numbers\n", n);
		if (write(fd[1], &n, sizeof(int)) < 0)
			return 3;
		if (write(fd[1], arr, sizeof(int) * n) < 0)
			return 4;
		printf("[child]Array sent\n");
		close(fd[1]); 						//close writing to pipe, after all is done
	}
	else
	{
		int	arr[10];
		int	n;
		int	i;
		int	sum;

		//Parent process
		close(fd[1]);						// close writing to pipe (parent only reads from pipe)
		if (read(fd[0], &n, sizeof(int)) < 0)
			return 5;
		printf("[parent]Receiving n = %d numbers\n", n);
		if (read(fd[0], arr, sizeof(int) * n) < 0)
			return 6;
		close(fd[0]);						// close reading from pipe, after all is done
		i = 0;
		sum = 0;
		printf("[parent]Summing an array of: ");
		while (i < n)
		{
			sum += arr[i];
			printf("%d ", arr[i]);
			i++;
		}
		printf("\n");
		printf("[parent]The result is: %d\n", sum);
		wait(NULL);							// just in case, to ensure that the child process finishes
	}

	return 0;
}

