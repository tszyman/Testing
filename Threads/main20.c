#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>
#define THREAD_NUM 8

pthread_mutex_t	mutex_fuel;
int				fuel = 50;

/* Recursive mutexes */

void	*routine()
{
	pthread_mutex_lock(&mutex_fuel);
	pthread_mutex_lock(&mutex_fuel);
	fuel += 50;
	printf("Incremented fuel to: %d\n", fuel);
	pthread_mutex_unlock(&mutex_fuel);
	pthread_mutex_unlock(&mutex_fuel);
	return 0;
}

int	main()
{
	pthread_t				th[THREAD_NUM];
	pthread_mutexattr_t		recursive_mutex_attr;
	int						i;

	pthread_mutexattr_init(&recursive_mutex_attr);
	pthread_mutexattr_settype(&recursive_mutex_attr, PTHREAD_MUTEX_RECURSIVE_NP);
	pthread_mutex_init(&mutex_fuel, &recursive_mutex_attr);
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
	pthread_mutexattr_destroy(&recursive_mutex_attr);
	pthread_mutex_destroy(&mutex_fuel);
	return 0;
}