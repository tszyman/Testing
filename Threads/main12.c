#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>
#include <errno.h>
#include <time.h>

/* Practical example for pthread_mutex_trylock */
/* 	chefs = threads
	stove = shared data (+mutex) */

pthread_mutex_t	stove_mutex[4];
int				stove_fuel[4] = {100, 100, 100, 100};

void	*routine()
{
	int	fuel_needed;
	int	i;

	i = 0;
	while (i < 4)
	{
		if (pthread_mutex_trylock(&stove_mutex[i]) == 0)
		{
			fuel_needed = (rand() % 30);
			if (stove_fuel[i] - fuel_needed < 0)
				printf("No more fuel. Going home.\n");
			else
			{
				stove_fuel[i] -= fuel_needed;
				usleep(500000);
				printf("Fuel left: %d\n", stove_fuel[i]);
			}
			pthread_mutex_unlock(&stove_mutex[i]);
			break;
		} else
		{
			if (i == 3)
			{
				printf("No stove available yet, waiting...\n");
				usleep(300000);
				i = 0;
			}
		}
		i++;
	}
	return 0;
}

int	main()
{
	pthread_t	th[10];
	int			i;

	srand(time(NULL));
	i = 0;
	while (i < 4)
	{
		pthread_mutex_init(&stove_mutex[i], NULL);
		i++;
	}
	i = 0;
	while ( i < 10)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
			perror("Failed to creade a thread");
		i++;
	}

	i = 0;
	while (i < 10)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("Failed to join thread");
		i++;
	}
	i = 0;
	while ( i < 4)
	{
		pthread_mutex_destroy(&stove_mutex[i]);
		i++;
	}
	return 0;
}