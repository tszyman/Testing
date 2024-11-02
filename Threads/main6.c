#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>
#include <time.h>

/* Get a return value from a thread */

void	*roll_dice()
{
	int	value;
	int	*result;

	value = rand() % 6 + 1;
	result = malloc(sizeof(int));
	*result = value;
	printf("Thread result: %p\n", result);
	return (void *) result;
}

int	main()
{
	pthread_t	th;
	int			*res;

	srand(time(NULL));
	if(pthread_create(&th, NULL, &roll_dice, NULL) != 0)
		return 1;
	if(pthread_join(th, (void **) &res) != 0)
		return 2;
	printf("Main res: %p\n", res);
	printf("Result: %d\n", *res);
	free(res);
	return 0;
}