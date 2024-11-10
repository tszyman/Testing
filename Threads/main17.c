#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>

#define THREAD_NUM 2

/* Detached threads */

void	*routine()
{
	sleep(1);
	printf("Finished execution.\n");
	return 0;
}

int	main()
{
	pthread_t	th[THREAD_NUM];
	int			i;

	i = 0;
	while (i < THREAD_NUM)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
			perror("Error creating thread");
		pthread_detach(th[i]);
		i++;
	}

	// i = 0;
	// while (i < THREAD_NUM)
	// {
	// 	if (pthread_join(th[i], NULL) != 0)
	// 		perror("Error joining thread");
	// 	i++;
	// }
	pthread_exit(0);
}