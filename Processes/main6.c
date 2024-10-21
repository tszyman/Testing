#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> //pipe, read, write - are here

/* Comminication between processes (using pipes) */
/* int fd[2] array of "keys" to read/write tfrom/to pipe */
/* fd[0] - read */
/* fd[1] - write */
int main()
{
	int	fd[2];
	int	id;
	int	x;
	int	y;

	if (pipe(fd) != 0)
	{
		printf("An error occurred while creating a pipe \n");
		return 1;
	}
	id = fork();
	if (id == -1)
	{
		printf("An error occured when forking.");
		return 4;
	}
	if (id == 0)
	{
		close(fd[0]); //we can close the read-end of the pipe immidiately, since child process does not read, just writes
		printf("[from Child process (ID: %d)]Input a number: ", id);
		scanf("%d", &x);
		if (write(fd[1], &x, sizeof(int)) == -1)
		{
			printf("An error occured writing to hte pipe!\n");
			return 2;
		}
		close(fd[1]); //close at the end as with the regular file descriptor
	}
	else
	{
		close(fd[1]); // we close the write-end, since in this process we only read from pipe
		if (read(fd[0], &y, sizeof(int)) == -1)
		{
			printf("An error occured reading from the pipe.");
			return 3;
		}
		close(fd[0]); //close file descriptor after redaing is finished
		printf("[from Main process (ID: %d)]Got from child process value: %d\n", id, y);
	}
	/* code */
	return 0;
}
