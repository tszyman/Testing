#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>
#include <time.h>

/* Get a return value from a thread with pthread_exit */

void	*roll_dice()
{
	int	value;
	int	*result;

	value = rand() % 6 + 1;
	result = malloc(sizeof(int));
	*result = value;
	sleep(2);
	printf("Thread result: %d\n", value);
	pthread_exit( (void *) result);
}

int	main()
{
	pthread_t	th;
	int			*res;

	srand(time(NULL));
	if(pthread_create(&th, NULL, &roll_dice, NULL) != 0)
		return 1;
	pthread_exit(0); 									// we're terminating the main thread (not terminating the process), but waiting for other threads to finish 
	if(pthread_join(th, (void **) &res) != 0)
		return 2;
	printf("Result: %d\n", *res);
	free(res);
	return 0;
}