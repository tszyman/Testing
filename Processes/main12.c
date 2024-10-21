#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/wait.h>

/* Getting exit status code in C */

int main()
{
	int	pid;
	int	err;
	int	wstatus;
	int	status_code;

	pid = fork();
	if (pid == -1)
		return 1;
	if (pid == 0)
	{
		// Child process
		err = execlp("ping", "ping", "-c", "3", "google.con", NULL);
		if (err == -1)
		{
			printf("Could not find program to execute.\n");
			return 2;
		}
	}
	else
	{
		// Parent process
		wait(&wstatus);
		if (WIFEXITED(wstatus))						//checking if the program has not been interrupted by an external signal
		{
			status_code = WEXITSTATUS(wstatus);		//checking the status code, that the program (in child process) finished with
			if (status_code == 0)
				printf("Success!\n");
			else
				printf("Failure with status code %d\n", status_code);
		}
		printf("Add some postprocessing here.\n");
	}
	return 0;
}
