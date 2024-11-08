#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>
#include <sys/syscall.h>

#define THREAD_NUM 2

/* WHat is pthread_t */

void	*routine(void *arg)
{
	pthread_t	th;
	int			i;
	
	th = pthread_self();
	i = *(int *)arg;
	printf("pthread #%d id from thread (pthread API level): %lu\n", i, th);
	printf("Thread #%d system id (OS level): %d\n", i, (pid_t)syscall(SYS_gettid));
	free(arg);
	return 0;
}

int	main()
{
	pthread_t	th[THREAD_NUM];
	int			i;
	int			*a;

	i = 0;
	while (i < THREAD_NUM)
	{
		a = malloc(sizeof(int));
		if (!a)
			return 0;
		*a = i;
		if(pthread_create(&th[i], NULL, &routine, a) != 0)
			perror("Failed to create a thread.");
		printf("pthread #%d id from main (pthread API level): %lu\n", i, th[i]);
		i++;
	}

	i = 0;
	while (i < THREAD_NUM)
	{
		if(pthread_join(th[i], NULL) != 0)
			perror("Failed to join a thread.");
		i++;
	}
	return 0;
}