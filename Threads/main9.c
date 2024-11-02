#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>

/* Difference beteen trylock and lock in C */

pthread_mutex_t mutex;

void	*routine()
{
	pthread_mutex_lock(&mutex);
	printf("Got lock\n");
	sleep(1);
	pthread_mutex_unlock(&mutex);
	return 0;
}

int	main()
{
	pthread_t	th[4];
	int			i;

	pthread_mutex_init(&mutex, NULL);
	i = 0;
	while ( i < 4)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
			perror("Error at creating a thread.");
		i++;
	}
	i = 0;
	while ( i < 4)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("Error at joining a thread.");
		i++;
	}
	pthread_mutex_destroy(&mutex);
	return 0;
}