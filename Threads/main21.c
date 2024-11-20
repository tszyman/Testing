#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>
#include <semaphore.h>
#define THREAD_NUM 4

/* Semaphores introduction */

sem_t	semaphore;

void	*routine(void *args)
{
	sem_wait(&semaphore);
	sleep(1);
	printf("Hello from thread %d\n", *(int *)args);
	sem_post(&semaphore);
	free(args);
	return 0;
}

int	main()
{
	pthread_t	th[THREAD_NUM];
	int			i;
	int			*a;

	sem_init(&semaphore, 0, 2);					// options: semaphore, 0/1 - one/multi process, 1 - initial semaphore value
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