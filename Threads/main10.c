#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>

/* Condition variables in C */

pthread_mutex_t mutex_fuel;
int fuel;

void	*fuel_filling()
{
	int	i;

	i = 0;
	while (i < 5)
	{
		pthread_mutex_lock(&mutex_fuel);
		fuel += 15;
		printf("Filling fuel... %d\n", fuel);
		pthread_mutex_unlock(&mutex_fuel);
		i++;
	}
	return 0;
}
void	*car()
{
	pthread_mutex_lock(&mutex_fuel);
	fuel -= 40;
	printf("Got fuel. Now left %d\n", fuel);
	pthread_mutex_unlock(&mutex_fuel);
	return 0;
}

int	main()
{
	pthread_t	th1;
	pthread_t	th2;
	
	fuel = 0;
	pthread_mutex_init(&mutex_fuel, NULL);
	if (pthread_create(&th1, NULL, &car, NULL) != 0)
		perror("Failed to create a thread");
	if (pthread_create(&th2, NULL, &fuel_filling, NULL) != 0)
		perror("Failed to create a thread");
	if (pthread_join(th1, NULL) != 0)
		perror("Failed to join thread");
	if (pthread_join(th2, NULL) != 0)
		perror("Failed to join thread");
	pthread_mutex_destroy(&mutex_fuel);
	return 0;
}