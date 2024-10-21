#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <signal.h>
#include <bits/sigaction.h>
#include <asm-generic/signal-defs.h>


/* Handling signals */

void	handle_tstp()
{
	printf("Stop not allowed\n");
}

int main()
{
	int	x;
	struct sigaction sa;
	sa.sa_handler = &handle_tstp;
	sa.sa_flags = SA_RESTART;

	sigaction(SIGTSTP, &sa, NULL);

	printf("Input number: ");
	scanf("%d", &x);
	printf("Result %d * 5 is: %d\n", x, x * 5);
	return 0;
}
