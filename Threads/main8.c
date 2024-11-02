#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>

/* Practical example of using threads */

int	primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void	*routine(void *arg)
{
	int	index;
	int	sum;
	int	j;

	index = *(int *)arg;
	sum = 0;
	j = 0;
	while (j < 5)
	{
		sum += primes[index + j];
		j++;
	}
	*(int *)arg = sum;
	printf("Partial sum: %d\n", sum);
	return arg;
}

int	main()
{
	pthread_t	th[2];
	int			i;
	int			*a;
	int			global_sum;

	i = 0;
	while (i < 2)
	{
		a = malloc(sizeof(int));
		*a = i * 5;
		if (pthread_create(&th[i], NULL, &routine, a) != 0)
			perror("Failed to create thread.");
		i++;
	}
	global_sum = 0;
	i = 0;
	while (i < 2)
	{
		int	*res;
		if (pthread_join(th[i], (void **)&res) != 0)
			perror("Failed to join the thread.");
		global_sum += *res;
		free(res);
		i++;
	}
	printf("Global sum: %d\n", global_sum);
	return 0;
}