#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>
#include <semaphore.h>

#define THREAD_NUM 4

sem_t			sem;

/* Getting the value of the semaphore */

void	*routine(void *args)
{
	int	index;
	int	sem_val;

	index = *(int *)args;
	sem_wait(&sem);
	sem_getvalue(&sem, &sem_val);
	printf("(%d)Current semaphore value is %d\n", index, sem_val);
	sem_post(&sem);
	free(args);
	return 0;
}

int	main()
{
	pthread_t	th[THREAD_NUM];
	int			i;
	int			*a;

	sem_init(&sem, 0, 4);
	i = 0;
	while (i < THREAD_NUM)
	{
		a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&th[i], NULL, &routine, a) != 0)
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
	sem_destroy(&sem);
	return 0;
}