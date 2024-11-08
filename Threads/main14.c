#define _XOPEN_SOURCE 600
#include <stdlib.h>
#include <stdio.h>
#define _XOPEN_SOURCE 600
#include <pthread.h>
#include <unistd.h>

/* Intro to barriers */

pthread_barrier_t	barrier;

void	*routine()
{
	// while (1)
	// {
		printf("Waiting at the barrier...\n");
		sleep(1);
		pthread_barrier_wait(&barrier);				//waiting for the right number of threads. Only after the number of threads are at the barrier - barrier lets to execute all them together.
		printf("We passed the barrier.\n");
		sleep(1);
	// }
	return 0;
}

int	main()
{
	pthread_t	th[5];
	int			i;

	pthread_barrier_init(&barrier, NULL, 5);
	i = 0;
	while (i < 5)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
			perror("Failed to create thread");
		i++;
	}

	i = 0;
	while (i < 5)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("Failed to join thread");
		i++;
	}
	pthread_barrier_destroy(&barrier);
	return 0;
}