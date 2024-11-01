#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>

/* Short introduction to threads (pthread) */

void	*routine()
{
	printf("Test from threads\n");
	sleep(3);
	printf("Ending thread\n");
	return 0;
}

int	main()
{
	pthread_t	t1;
	pthread_t	t2;

	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return 1;
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return 2;
	if (pthread_join(t1, NULL) != 0)							//like "wait", but for threads
		return 3;
	if (pthread_join(t2, NULL) != 0)
		return 4;
	return 0;
}