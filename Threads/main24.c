#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>

#define THREAD_NUM 4

pthread_mutex_t	mutex_fuel;
int				fuel;

/* Binary semaphores */

void	*routine()
{
	pthread_mutex_lock(&mutex_fuel);
	fuel += 50;
	printf("Current value is %d\n", fuel);
	pthread_mutex_unlock(&mutex_fuel);
	return 0;
}

int	main()
{
	pthread_t	th[THREAD_NUM];
	int			i;

	fuel = 50;
	pthread_mutex_init(&mutex_fuel, NULL);
	i = 0;
	while (i < THREAD_NUM)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
			perror("Error creating thread");	
		i++;
	}
	i = 0;

	while (i < THREAD_NUM)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("Error joining threads");
		i++;
	}
	pthread_mutex_destroy(&mutex_fuel);
	return 0;
}