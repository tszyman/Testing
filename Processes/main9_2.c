#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

/* How to use FIFO files to communicate between processes 2/2 - read */
int main()
{
	int	arr[5];
	int	fd;
	int	i;
	int	sum;

	fd = open("sum", O_RDONLY);
	if (fd == -1)
		return 1;
	if (read(fd, arr, sizeof(int) * 5) == -1)
		return 2;
	close(fd);
	sum = 0;
	i = 0;
	while (i < 5)
	{
		sum += arr[i];
		i++;
	}
	//write the result to FIFO
	fd = open("sum", O_WRONLY);
	if (fd == -1)
		return 3;
	if (write(fd, &sum, sizeof(int)) == -1)
		return 4;
	close(fd);
	return 0;
}