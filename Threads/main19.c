#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>
#define THREAD_NUM 8

pthread_mutex_t	mutex_fuel;
int				fuel = 50;

pthread_mutex_t	mutex_water;
int				water = 50;

/* Deadlocks in C */

void	*routine()
{
//	if (rand() % 2 == 0)
//	{
		pthread_mutex_lock(&mutex_fuel);				// one thread might lock fuel, while the other starts with locking the water
		sleep(1);
		pthread_mutex_lock(&mutex_water);				// but here - the one will wait until water is ready to be locked, but the other process waits for fuel to be ready to be locked.
//	}													// it will never happen, so both proceses will wait for each other.
//	else
//	{
//		pthread_mutex_lock(&mutex_water);
//		sleep(1);
//		pthread_mutex_lock(&mutex_fuel);
//	}
	fuel += 50;
	water = fuel;
	printf("Incremented fuel to: %d set water to %d\n", fuel, water);
	pthread_mutex_unlock(&mutex_fuel);
	pthread_mutex_unlock(&mutex_water);
	return 0;
}

int	main()
{
	pthread_t	th[THREAD_NUM];
	int			i;

	pthread_mutex_init(&mutex_fuel, NULL);
	pthread_mutex_init(&mutex_water, NULL);
	i = 0;
	while (i < THREAD_NUM)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
			perror("Failed to create thread");
		i++;
	}

	i = 0;
	while (i < THREAD_NUM)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("Failed to jion thread");
		i++;
	}
	printf("Fuel: %d\n", fuel);
	pthread_mutex_destroy(&mutex_fuel);
	pthread_mutex_destroy(&mutex_water);
	return 0;
}