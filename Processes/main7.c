#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/* A program, that sums up an array, but using two processes
One process summs elements of half of the array, writes the oucome to pipe.
Main process, reads from pipe and summs with the rest of the array */

int main()
{
	int	id;
	int	fd[2];
	int	i;
	int	start;
	int	end;
	int	sum;
	int	sum_from_child;
	int	sum_total;
	int	arr[] = {1, 2, 3, 4, 1, 2};
	int	arr_size;

	arr_size = sizeof(arr) / sizeof(int);
	if (pipe(fd) != 0)
	{
		printf("An error occurred while creating a pipe \n");
		return 1;
	}
	id = fork();
	if (id == -1)
	{
		printf("Error on fork");
		return 2;
	}
	if (id == 0)
	{
		start = 0;
		end = arr_size/2;
	}
	else
	{
		start = arr_size/2;
		end = arr_size;
	}
	sum = 0;
	i = start;
	while (i < end)
	{
		sum += arr[i];
		i++;
	}
	printf("Calculated partial sum: %d \n", sum);
	if (id == 0)
	{
		close(fd[0]);
		if (write(fd[1], &sum, sizeof(sum)) == -1)
			return 3;
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		if (read(fd[0], &sum_from_child, sizeof(sum_from_child)) == -1)
			return 4;
		close(fd[0]);
		sum_total = sum + sum_from_child;
		printf("Total sum: %d\n", sum_total);
		wait(NULL);
	}
	return 0;
}
