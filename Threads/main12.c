#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>
#include <errno.h>
#include <time.h>

/* Practical example for pthread_mutex_trylock */
/* 	chefs = threads
	stove = shared data (+mutex) */

pthread_mutex_t	stove_mutex;
int				stove_fuel;

void	*routine()
{
	int	fuel_needed;

	pthread_mutex_lock(&stove_mutex);
	fuel_needed = (rand() % 30);
	if (stove_fuel - fuel_needed < 0)
		printf("No more fuel. Going home.\n");
	else
	{
		stove_fuel -= fuel_needed;
		usleep(500000);
		printf("Fuel left: %d\n", stove_fuel);
	}
	pthread_mutex_unlock(&stove_mutex);
	return 0;
}

int	main()
{
	pthread_t	th[10];
	int			i;

	srand(time(NULL));
	pthread_mutex_init(&stove_mutex, NULL);
	stove_fuel = 100;
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
	pthread_mutex_destroy(&stove_mutex);
	return 0;
}