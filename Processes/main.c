#include <stdio.h>
#include <stdlib.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

int	main()
{
	int	x;

	x = 17;
	printf("\033[0;31mHello world %d times!\033[0m \n", x);
	printf("%sHello world %d times!%s \n", KGRN, x, KNRM);
	return 0;
}