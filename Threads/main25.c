#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>
#include <semaphore.h>

#define THREAD_NUM 4

sem_t			sem_fuel;
pthread_mutex_t	mutex_fuel;
int				fuel;

/* Difference between binary semaphores and mutexes */

void	*routine1()
{
	sem_wait(&sem_fuel);
	fuel += 50;
	printf("Current value is %d\n", fuel);
	return 0;
}

void	*routine2()
{
	sem_post(&sem_fuel);
	usleep(50000);
	return 0;
}


int	main()
{
	pthread_t	th[THREAD_NUM];
	int			i;

	fuel = 50;
	pthread_mutex_init(&mutex_fuel, NULL);
	sem_init(&sem_fuel, 0, 1);
	i = 0;
	while (i < THREAD_NUM)
	{
		if (i % 2 == 0)
		{
			if (pthread_create(&th[i], NULL, &routine1, NULL) != 0)
				perror("Error creating thread");
		}
		else
		{
			if (pthread_create(&th[i], NULL, &routine2, NULL) != 0)
				perror("Error creating thread");
		}	
		i++;
	}
	i = 0;

	while (i < THREAD_NUM)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("Error joining threads");
		i++;
	}
	sem_destroy(&sem_fuel);
	pthread_mutex_destroy(&mutex_fuel);
	return 0;
}