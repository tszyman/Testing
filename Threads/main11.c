#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>

/* Signaling for condition variables (signal vs broadcast) */

pthread_mutex_t mutex_fuel;
pthread_cond_t cond_fuel;
int fuel;

void	*fuel_filling()
{
	int	i;

	i = 0;
	while (i < 5)
	{
		pthread_mutex_lock(&mutex_fuel);
		fuel += 30;
		printf("Filling fuel... %d\n", fuel);
		pthread_mutex_unlock(&mutex_fuel);
		pthread_cond_broadcast(&cond_fuel);			//signal -> sent to one thread; broadcast -> sent to all threads
		sleep(1);
		i++;
	}
	return 0;
}
void	*car()
{
	pthread_mutex_lock(&mutex_fuel);
	while (fuel < 40)
	{
		printf("Not enough fuel. Waiting...\n");
		pthread_cond_wait(&cond_fuel, &mutex_fuel);
		// Equivalent to:
		// pthread_mutex_unlock(&mutex_fuel);
		// wait for singal on cond_fuel
		// pthread_mutex_lock(&mutex_fuel);
	}
	fuel -= 40;
	printf("Got fuel. Now left %d\n", fuel);
	pthread_mutex_unlock(&mutex_fuel);
	return 0;
}

int	main()
{
	pthread_t	th[6];
	int			i;
	
	fuel = 0;
	i = 0;
	pthread_mutex_init(&mutex_fuel, NULL);
	pthread_cond_init(&cond_fuel, NULL);
	while (i < 6)
	{
		if (i == 4 || i == 5)
		{
			if (pthread_create(&th[i], NULL, &fuel_filling, NULL) != 0)
				perror("Failed to create a thread");
		} else 
		{
			if (pthread_create(&th[i], NULL, &car, NULL) != 0)
				perror("Failed to create a thread");
		}	
		i++;
	}
	i = 0;
	while (i < 6)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("Failed to join thread");
		i++;
	}
	pthread_mutex_destroy(&mutex_fuel);
	pthread_cond_destroy(&cond_fuel);
	return 0;
}