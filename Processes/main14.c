#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/wait.h>
#include <fcntl.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"


/* Redirecting standard output in C */
/* Default file descriptors:
	0 - STDIN
	1 - STDOUT
	2 - STDERR

	dup2: duplicates file descriptor, closes the second fd, and redirects 
			(in this case, closes fd = 1 (STDOUT) and redirects everything to fd = file (ping_results.txt))
 */

int main()
{
	int	pid;
	int	err;
	int	wstatus;
	int	status_code;
	int	file;

	pid = fork();
	if (pid == -1)
		return 1;
	if (pid == 0)
	{
		// Child process
		file = open("ping_results.txt", O_WRONLY | O_CREAT, 0777);
		if (file == -1)
			return 3;
		printf("The fd to ping_results: %d\n", file);
		dup2(file, STDOUT_FILENO);
		close(file);


		err = execlp("ping", "ping", "-c", "3", "google.com", NULL);
		if (err == -1)
		{
			printf("%sCould not find program to execute.%s\n", KRED, KNRM);
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
				printf("%sSuccess!%s\n", KGRN, KNRM);
			else
				printf("%sFailure with status code %d%s\n", KRED, status_code, KNRM);
		}
		printf("Add some postprocessing here.\n");
	}
	return 0;
}
