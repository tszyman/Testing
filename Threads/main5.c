#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>

/* creating threads in a loop */

int	mails;
pthread_mutex_t mutex;

void	*routine()
{
	int	i;

	i = 0;
	while (i < 10000000)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
		i++;
	}
	return 0;
}

int	main()
{
	pthread_t	th[4];
	int			i;

	pthread_mutex_init(&mutex, NULL);
	i = 0;
	mails = 0;
	while (i < 4)
	{
		if (pthread_create(th + i, NULL, &routine, NULL) != 0)
		{
			perror("Failed to create thread.");
			return 1;
		}
		printf("Thread %d has started.\n", i);
		if (pthread_join(th[i], NULL) != 0)
			return 2;
		printf("Thread %d has finished execution.\n", i);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	printf("Number of emails: %d\n", mails);
	return 0;
}