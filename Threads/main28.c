#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>
#include <time.h>

/* Thread Pools */

// Our representation of the task to be dealt with
typedef struct Task
{
	int	a;
	int	b;
} Task;

// Task Queue will hold the tasks to bo done of threads to reach from
Task	task_queue[256];
int		task_count = 0;

// function executing the task
void	execute_task(Task *task)
{
	int	result;

	result = task->a + task->b;
	printf("The sum of %d and %d is %d\n", task->a, task->b, result);
}


int	main()
{
	Task	t1 = {
		.a = 5,
		.b = 10
	};

	execute_task(&t1);
	return 0;
}