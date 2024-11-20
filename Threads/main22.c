#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>
#include <semaphore.h>
#define THREAD_NUM 16

/* Practical examples using semaphores (Login Queue) */

sem_t	semaphore;

void	*routine(void *args)
{
	printf("(%d) Waiting in a login queue\n", *(int *)args);
	sem_wait(&semaphore);
	printf("(%d) Logged in\n", *(int *)args);
	sleep(rand() %5 + 1);
	printf("(%d) Logged out\n", *(int *)args);
	sem_post(&semaphore);
	free(args);
	return 0;
}

int	main()
{
	pthread_t	th[THREAD_NUM];
	int			i;
	int			*a;

	sem_init(&semaphore, 0, 12);					// options: semaphore, 0/1 - one/multi process, 1 - initial semaphore value
	i = 	0;
	while (i < THREAD_NUM)
	{
		a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&th[i], NULL, &routine, a) != 0)
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
	sem_destroy(&semaphore);
	return 0;
}