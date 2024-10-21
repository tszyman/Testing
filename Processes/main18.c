#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/* Background and foreground processes */

int main()
{
	int	x;

	printf("Input number: ");
	scanf("%d", &x);
	printf("Result %d * 5 is: %d\n", x, x * 5);
	return 0;
}
