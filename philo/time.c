# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <limits.h>

int main()
{
	struct timeval tv1, tv2;
	long	sec;

	gettimeofday(&tv1, NULL);
	printf("Seconds since Jan 1, 1970: %ld\n", tv1.tv_sec);
	usleep(4000000);
	gettimeofday(&tv2, NULL);
	sec = tv2.tv_sec - tv1.tv_sec;
	printf("Seconds since Jan 1, 1970: %ld\n", tv2.tv_sec);
	printf("%ld\n", sec);
	return 0;
}