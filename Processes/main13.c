#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

/* How to execute another program in C (using exec) */
/* This exercise should be in fact before ex. 11 */
/* execlpe:
	l/v - list of parameters or given as a vector (array) 
	p - shoud path be checked
	e - enviromental variables to be given
*/

int main()
{
	int	err;

	execlp("ping2", "ping", "-c", "3", "google.com", NULL);
	err = errno;
	printf("Ping finished executing with error %d\n", err);
	return 0;
}
