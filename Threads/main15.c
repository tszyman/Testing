#define _XOPEN_SOURCE 600
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>
#include <time.h>

#define THREAD_NUM 8					// macro defining number of threads

/* Practical example to barriers */

pthread_barrier_t	barrier_rolled_dice;
pthread_barrier_t	barrier_calculated;
int					dice_values[THREAD_NUM];
int					status[THREAD_NUM] = {0};

void	*roll_dice(void *args)
{
	int	index;

	index = *(int *)args;
	while(1)
	{
		dice_values[index] = rand() % 6 + 1;
		pthread_barrier_wait(&barrier_rolled_dice);
		pthread_barrier_wait(&barrier_calculated);
		if (status[index] == 1)
			printf("(%d rolled %d) I won\n", index, dice_values[index]);
		else
			printf("(%d rolled %d) I lost\n", index, dice_values[index]);
	}
	free(args);
	return 0;
}

int	main()
{
	int			i;
	int			max;
	int			*a;
	pthread_t	th[THREAD_NUM];
	
	srand(time(NULL));
	pthread_barrier_init(&barrier_rolled_dice, NULL, THREAD_NUM + 1);
	pthread_barrier_init(&barrier_calculated, NULL, THREAD_NUM + 1);
	i = 0;
	while (i < THREAD_NUM)
	{
		a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&th[i], NULL, &roll_dice, a) != 0)
			perror("Failed to create a thread");
		i++;
	}
	while(1)
	{
		pthread_barrier_wait(&barrier_rolled_dice);
		// Calculating the winner
		max = 0;
		i = 0;
		while (i < THREAD_NUM)
		{
			if (dice_values[i] > max)
				max = dice_values[i];
			i++;
		}

		i = 0;
		while (i < THREAD_NUM)
		{
			if (dice_values[i] == max)
				status[i] = 1;
			else
				status[i] = 0;
			i++;
		}
		printf("======== NEW ROUND ========\n");
		sleep(1);
		pthread_barrier_wait(&barrier_calculated);
	}
	i = 0;
	while (i < THREAD_NUM)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("Failed to join thread");
		i++;
	}
	pthread_barrier_destroy(&barrier_rolled_dice);
	pthread_barrier_destroy(&barrier_calculated);
	return 0;
}