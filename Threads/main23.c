#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>
#include <time.h>
#include <semaphore.h>

#define THREAD_NUM 8

/* Producer - consumer problem */

sem_t	sem_empty;
sem_t	sem_full;
pthread_mutex_t	mutex_buffer;

int	buffer[10];
int	count = 0;

void	*producer()
{
		int	x;
	while(1)
	{
		// Produce
		x = rand() % 100;
		sleep(1);

		// Add to the buffer
		sem_wait(&sem_empty);
		pthread_mutex_lock(&mutex_buffer);
		buffer[count] = x;
		count++;
		pthread_mutex_unlock(&mutex_buffer);
		sem_post(&sem_full);
	}
	return 0;
}

void	*consumer()
{
	int	y;

	while(1)
	{

		// Remove from the buffer
			sem_wait(&sem_full);
		pthread_mutex_lock(&mutex_buffer);
		y = buffer[count - 1];
		count--;
		pthread_mutex_unlock(&mutex_buffer);
			sem_post(&sem_empty);
		// Consume
		printf("Got %d\n", y);
		// sleep(1);
	}
	return 0;
}

int	main()
{
	pthread_t	th[THREAD_NUM];
	int			i;

	pthread_mutex_init(&mutex_buffer, NULL);
	sem_init(&sem_empty, 0, 10);
	sem_init(&sem_full, 0, 0);
	srand(time(NULL));
	i = 0;
	while (i < THREAD_NUM)
	{
		if(i % 2 == 0)
		{
			if(pthread_create(&th[i], NULL, &producer, NULL) != 0)
				perror("Error creating a thread");
		}
		else
		{
			if(pthread_create(&th[i], NULL, &consumer, NULL) != 0)
				perror("Erorr creating a thread");
		}
		i++;
	}
	i = 0;
	while ( i < THREAD_NUM)
	{
		if(pthread_join(th[i], NULL) != 0)
			perror("Error joining a string");
		i++;
	}
	pthread_mutex_destroy(&mutex_buffer);
	sem_destroy(&sem_empty);
	sem_destroy(&sem_full);
	return 0;
}