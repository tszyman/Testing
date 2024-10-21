#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

/* How to use FIFO files to communicate between processes 1/2 - write */
int main()
{
	int arr[5];
	int	i;
	int	fd;
	int	sum;

	srand(time(NULL));
	i = 0;
	while (i < 5)
	{
		arr[i] = rand() % 10;
		printf("Generated %d\n", arr[i]);
		i++;
	}
	fd = open("sum", O_WRONLY);
	if (fd == -1)
		return 1;
	if (write(fd, arr, sizeof(int) * 5) == -1)
		return 2;
	close(fd);
	//read the result back from FIFO
	fd = open("sum", O_RDONLY);
	if (fd == -1)
		return 3;
	if (read(fd, &sum, sizeof(int)) == -1)
		return 4;
	printf("The result is %d\n", sum);
	close(fd);
	return 0;
}