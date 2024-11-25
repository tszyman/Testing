#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>
#include <time.h>

#define THREAD_NUM 8

/* Thread Pools with function pointers in C */

// Our representation of the task to be dealt with
typedef struct Task
{
	void (*task_function)(int, int);
	int	arg1, arg2;
} Task;

// Task Queue will hold the tasks to bo done of threads to reach from
Task	task_queue[256];
int		task_count = 0;

pthread_mutex_t	mutex_queue;	//will protect elements of the queue from being taken by two threads at the same time
pthread_cond_t	cond_queue;

void	sum_and_product(int a, int b)
{
	int sum = a + b;
	int prod = a * b;
	printf("Sum and product of %d and %d is %d and %d respectively\n", a, b, sum, prod);
}

// function executing the task
void	execute_task(Task *task)
{
	task->task_function(task->arg1, task->arg2);
}
void	submit_task(Task task)
{
	pthread_mutex_lock(&mutex_queue);
	task_queue[task_count] = task;
	task_count++;
	pthread_mutex_unlock(&mutex_queue);
	pthread_cond_signal(&cond_queue);
}

void	*start_thread()
{
	while(1)
	{
		Task	task;
		int		i;

		pthread_mutex_lock(&mutex_queue);
		while(task_count == 0)
			pthread_cond_wait(&cond_queue, &mutex_queue);
		task = task_queue[0];
		i = 0;
		while (i < task_count - 1)
		{
			task_queue[i] = task_queue[i + 1];
			i++;
		}
		task_count--;
		pthread_mutex_unlock(&mutex_queue);
		execute_task(&task);
	}
}

int	main()
{
	pthread_t	th[THREAD_NUM];
	pthread_mutex_init(&mutex_queue, NULL);
	pthread_cond_init(&cond_queue, NULL);
	int			i;

	i = 0;
	while (i < THREAD_NUM)
	{
		if (pthread_create(&th[i], NULL, &start_thread, NULL) != 0)
			perror("Error creating the thread.");
		i++;
	}

	i = 0;
	srand(time(NULL));
	while ( i < 100)
	{
		Task	t = {
			.task_function = &sum_and_product,
			.arg1 = rand() % 100,
			.arg2 = rand() % 100
		};
		submit_task(t);
		i++;
	}

	i = 0;
	while (i < THREAD_NUM)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("Error joining the thread.");
		i++;
	}
	pthread_mutex_destroy(&mutex_queue);
	pthread_cond_destroy(&cond_queue);
	return 0;
}