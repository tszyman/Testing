#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>

#define THREAD_NUM 2

pthread_mutex_t	mutex_fuel = PTHREAD_MUTEX_INITIALIZER;		//Don't have to call init and destroy anymore
pthread_cond_t	cond_fuel = PTHREAD_COND_INITIALIZER;		//Don't have to call init and destroy anymore


/* Static initializers */

void	*routine()
{
	return 0;
}

int	main()
{
	pthread_t		th[THREAD_NUM];

	int				i;

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
			perror("Error joining thread");
		i++;
	}
	return 0;
}