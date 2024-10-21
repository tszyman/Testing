#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

/* Introduction to FIFOs (aka named pipes) */
int main()
{
	int	fd;
	int	x;

	if (mkfifo("myfifo1", 0777) == -1)	//check for errors when creating fifo file
	{
		if (errno != EEXIST)			//except for when it already exists
		{
			printf("Could not create fifo file.\n");
			return 1;
		}
	}
	fd = open("myfifo", O_WRONLY);
	if (fd == -1)
		return 3;
	x = 97;
	if (write(fd, &x, sizeof(x)) == -1)
		return 2;
	close(fd);
	return 0;
}
