#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>

/* How to pass arguments to threads in C */

int	primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void	*routine(void *arg)
{
	int	index;

	index = *(int *)arg;
	printf("%d ", primes[index]);
	free(arg);
	return 0;
}

int	main()
{
	pthread_t	th[10];
	int			i;
	int			*a;

	i = 0;
	while (i < 10)
	{
		a = malloc(sizeof(int));
		if(!a)
			return 0;
		*a = i;
		if(pthread_create(&th[i], NULL, &routine, a) != 0)
			perror("Failed to create thread.");
		i++;
	}
	i = 0;
	while (i < 10)
	{
		if(pthread_join(th[i], NULL) != 0)
			perror("Failed to join thread.");
		i++;
	}
	return 0;
}