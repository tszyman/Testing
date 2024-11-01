#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>

/* Race conditions */

int	mails;

void	*routine()
{
	int	i;

	i = 0;
	while (i < 1000000)
	{
		mails++;
		i++;
	}
	return 0;
}

int	main()
{
	pthread_t	t1;
	pthread_t	t2;

	mails = 0;
	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return 1;
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return 2;
	if (pthread_join(t1, NULL) != 0)
		return 3;
	if (pthread_join(t2, NULL) != 0)
		return 4;
	printf("Number of emails: %d\n", mails);
	return 0;
}