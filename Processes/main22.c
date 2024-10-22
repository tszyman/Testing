#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <string.h>
#include <sys/wait.h>
#include <time.h>

/* Sending a string through a pipe */

int main()
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		return 1;
	
	pid = fork();
	if (pid == -1)
		return 2;
	
	if (pid == 0)
	{
		//Child process
		char	str[200];
		int		str_len;

		close(fd[0]);
		printf("[child]Input string: ");
		fgets(str, 200, stdin);
		str[strlen(str) - 1] = '\0';			//replacing last character "\n" with "\0"
		str_len = strlen(str) + 1;
		printf("[child]Sending length of the string (%d chars, %d letters + null terminator)\n", str_len, str_len - 1);
		if (write(fd[1], &str_len, sizeof(int)) == -1)
			return 3;
		printf("[child]Sending the string of %d chars (+ null terminator)\n", str_len - 1);
		if (write(fd[1], str, sizeof(char) * str_len) == -1)
			return 4;
		printf("[child]String has been sent.\n");
		close(fd[1]);
	}
	else
	{
		//Parent process
		char	str[200];
		int		str_len;

		close(fd[1]);
		if (read(fd[0], &str_len, sizeof(int)) == -1)
			return 5;
		printf("[parent]Receiving a string of %d chars (+ null terminator)\n", str_len - 1);
		if (read(fd[0], str, sizeof(char) * str_len) == -1)
			return 6;
		printf("[parent]Recieved string: %s\n", str);
		close(fd[0]);
		wait(NULL);
	}
	return 0;
}
