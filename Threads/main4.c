#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>

/* mutex in C */

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
	pthread_t	t1;
	pthread_t	t2;
	pthread_t	t3;
	pthread_t	t4;

	pthread_mutex_init(&mutex, NULL);
	mails = 0;
	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return 1;
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return 2;
	if (pthread_create(&t3, NULL, &routine, NULL) != 0)
		return 3;
	if (pthread_create(&t4, NULL, &routine, NULL) != 0)
		return 4;
	if (pthread_join(t1, NULL) != 0)
		return 5;
	if (pthread_join(t2, NULL) != 0)
		return 6;
	if (pthread_join(t3, NULL) != 0)
		return 7;
	if (pthread_join(t4, NULL) != 0)
		return 8;
	pthread_mutex_destroy(&mutex);
	printf("Number of emails: %d\n", mails);
	return 0;
}