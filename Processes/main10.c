#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include <time.h>

/* Two way communication between processes (using pipes) in C 
   The main outcome is that it's better to use two, unidirectional pipes (P=>C, C=>P)
   than one, bidirectional (P<=>C) 
   If we would use biderectional pipe, it's good to put wait after sending values P=>C, wait(), P<=C */

int main()
{
	int	p1[2];
	int	p2[2];
	int	pid;
	int	x;
	int	y;

	//pipe p1: P<=C (parent reads, child writes)
	//pipe p2: P=>C (parent writes, child reads)
	if (pipe(p1) == -1)
		return 1;
	if (pipe(p2) == -1)
		return 1;
	pid = fork();
	if (pid == -1)
		return 2;
	if (pid == 0)
	{
		//Child process - reading from pipe
		close(p2[1]); //
		close(p1[0]);
		if (read(p2[0], &x, sizeof(x)) == -1)
			return 3;
		printf("[child]Received %d\n", x);
		x *= 4;
		if (write(p1[1], &x, sizeof(x)) == -1)
			return 4;
		printf("[child]Wrote %d\n", x);
		close(p2[0]);
		close(p1[1]);
	}
	else
	{
		//Parent process - writing
		srand(time(NULL));
		y = rand() % 10;
		if (write(p2[1], &y, sizeof(y)) == -1)
			return 5;
		//wait(NULL);
		//printf("[main]Generated %d\n", y);
		if (read(p1[0], &y, sizeof(y)) == -1)
			return 6;
		printf("[main]Result: %d\n", y);
		close(p2[0]);
		close(p1[1]);
	}
	return 0;
}
