#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/* The fork() function in C */

int	main()
{
	int	id;

	id = fork();
	if (id != 0)
		id = fork();
	printf("Hello world from id: %d!\n", id);
	// if (id == 0)
	// 	printf("Hello from a child process!\n");
	// else
	// 	printf("Hello from the main process!\n");
	return 0;
}
